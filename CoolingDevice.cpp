//
// Created by otto001 on 9/7/20.
//

#include "CoolingDevice.h"
#include "Control.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include "utils.h"


CoolingDevice::CoolingDevice(Control *control) : control(control) {

}

const std::filesystem::path &CoolingDevice::getPath() const {
    return path;
}

const std::string &CoolingDevice::getName() const {
    return name;
}

int CoolingDevice::getIndex() const {

    std::string fileName = path.filename();
    size_t last_index = fileName.find_last_not_of("0123456789");
    std::string digits = fileName.substr(last_index + 1);
    int result = -1;
    try {
        result = (int) std::stoi(digits);
    } catch (std::invalid_argument &e) {
        result = -1;
    } catch (std::out_of_range &e) {
        result = -1;
    }

    return result;
}


std::filesystem::path CoolingDevice::getHwmonPath() const {
    return path.parent_path();
}

std::filesystem::path CoolingDevice::getPwmPath() const {
    return getPath();
}

std::filesystem::path CoolingDevice::getFanPath() const {
    return getHwmonPath().append("fan" + std::to_string(getIndex()));
}


bool CoolingDevice::setSpeed(double speed, bool force) {
    speed = std::min(std::max(speed, 0.0), 1.0);
    auto speedInt = (int) round(speed * 255);

    auto minSpeedInt = (int) round(minSpeed * 255);
    auto startSpeedInt = (int) round(startSpeed * 255);

    if (!isPump) {
        if (speedInt > 0 && speedInt < minSpeedInt) {
            speed = minSpeed;
            speedInt = minSpeedInt;
        }
        if (speedInt >= minSpeedInt && speedInt < startSpeedInt && readRpm() == 0) {
            speed = startSpeed;
            speedInt = startSpeedInt;
            std::cout << "start help: " << name << std::endl;
        }
    }

    if (!force && currentSetSpeedInt == speedInt) {
        return true;
    }

    std::ofstream file;
    file.open(path, std::ios::out | std::ios::trunc);

    if (file.is_open()) {

        file << speedInt;
        file.close();
        currentSetSpeedInt = speedInt;
        currentSetSpeed = speed;
        return true;
    }
    std::cerr << "Failed to set speed of cooling device " << name << "!" << std::endl;

    return false;
}

bool CoolingDevice::setToManual() {
    std::string enablePath = getPwmPath();
    enablePath.append("_enable");

    std::ofstream file;
    file.open(enablePath, std::ios::out | std::ios::trunc);

    if (file.is_open()) {
        file << 1;
        file.close();

        setSpeed(currentSetSpeed, true);
        return true;
    }
    std::cerr << "Failed to set mode of cooling device " << name << " to manual!" << std::endl;
    return false;
}

int CoolingDevice::readRpm() {
    auto inputPath = std::string(getFanPath()) + "_input";
    return readIntFromPath(inputPath);
}

ThermalZone *CoolingDevice::getHottestZone() {
    ThermalZone *hottestZone = nullptr;
    currentHighScore = -1;
    for (auto zone : thermalZones) {
        auto score = zone->getScore();
        if (score > currentHighScore) {
            currentHighScore = score;
            hottestZone = zone;
        }
    }
    return hottestZone;
}

bool CoolingDevice::load(YAML::Node node) {

    path = readYamlField<std::string>(node, "path");
    name = readYamlField<std::string>(node, "name");


    lazinessStart = readYamlField<double>(node, "laziness-start", 0.6);
    lazinessStop = readYamlField<double>(node, "laziness-stop", 0.6);

    linearity = readYamlField<double>(node, "linearity", 0.0);


    startSpeed = readYamlField<double>(node, "start-speed", 0.0);
    minSpeed = readYamlField<double>(node, "min-speed", startSpeed);

    startSpeed /= 100.0;
    minSpeed /= 100.0;

    isPump = readYamlField<bool>(node, "is-pump", false);

    try {
        auto curveString = readYamlField<std::string>(node, "rpm-curve");

        size_t start = 0;
        for (int &rpm : rpmCurve) {
            auto end = curveString.find('-', start);
            if (end == -1) end = curveString.size();
            rpm = parseInt(curveString.substr(start, end - start));
            start = end + 1;
        }

    } catch (LoadingException& e) {
    }

    if (isPump) {
        for (int i = 0; i < sizeof(rpmCurve)/sizeof(*rpmCurve)-1; i++) {
            if (rpmCurve[i]*1.1 < rpmCurve[i+1]) {
                startSpeed = (i+1)/11.0;
                break;
            }
        }
    }

    auto thermalZoneNames =  readYamlField<std::vector<std::string>>(node, "thermal-zones");
    for (auto &thermalZoneName : thermalZoneNames) {
        ThermalZone *zone = control->getThermalZone(thermalZoneName);
        if (zone) {
            thermalZones.push_back(zone);
        }
    }

    return true;
}

bool CoolingDevice::init() {
    setToManual();
    return true;
}

void CoolingDevice::update() {
    checkIsResponsive();

    auto hottestZone = getHottestZone();
    double deltaSeconds = double(control->getInterval()) / 1000.0;


    if (currentHighScore < 1) {
        buildUp -= buildUp*0.25*deltaSeconds;
    } else if (currentHighScore < 2) {
        double target = (1 + currentHighScore - 1) * (buildUpThreshold / 10);
        buildUp += (target - buildUp) * 0.15*deltaSeconds;
    } else if (currentHighScore < 3) {
        double target = (1 + currentHighScore - 2) * buildUpThreshold;
        buildUp += std::max((target - buildUp) * 0.5, 0.0)*deltaSeconds;
    } else {
        buildUp = buildUpThreshold * 3;
    }

    bool started = currentSetSpeed != 0;
    if (!started && buildUp > buildUpThreshold * lerp(1.0, 1.5, lazinessStart)) {
        started = true;
    } else if (started && buildUp < buildUpThreshold * lerp(1.0, 0, lazinessStop)) {
        started = false;
    }

    double targetSpeed = currentSetSpeed;
    if (!started) {
        targetSpeed = 0;
    } else {
        auto curveSpeed = getSpeedFromCurve(currentHighScore - 2.0);
        auto delta = curveSpeed - currentSetSpeed;

        if (delta > 0.15) {
            targetSpeed = curveSpeed;
        } else if (std::abs(delta) > 0.03) {
            targetSpeed = currentSetSpeed + delta * 0.3;
        }

    }

    setSpeed(targetSpeed);
}

CoolingDevice *CoolingDevice::loadDevice(YAML::Node &node, Control *control) {
    auto device = new CoolingDevice(control);
    device->load(node);
    return device;
}

double CoolingDevice::getSpeedFromCurve(double x) {
    if (isPump) {
        return 0.25 + 0.25 * x;
    }
    double linear = x;
    double exponential = std::exp(4.6 * (x - 1.0));
    double result = lerp(exponential, linear, linearity);
    return result * (1.0 - minSpeed) + minSpeed;
}

bool CoolingDevice::checkIsResponsive() {
    double diff;
    double actualPwmSpeed = calculateActualPwmSpeed();

    if (currentSetSpeed == 0 && isPump && actualPwmSpeed < startSpeed) {
        diff = 0;
    } else {
        diff = std::abs(actualPwmSpeed - currentSetSpeed);
    }


    if (diff > 0.03) {
        unresponsiveCounter++;

        if (unresponsiveCounter > 8) {
            unresponsiveCounter = 0;
            std::cout << name << " unresponsive. Setting to manual mode..." << std::endl;
            setToManual();
            return false;
        }
    } else if (unresponsiveCounter > 0) {
        unresponsiveCounter++;
    }
    return true;
}

double CoolingDevice::calculateActualPwmSpeed() {
    int rpm = readRpm();
    if (rpm == -1) {
        return -1;
    }

    uint16_t i = 0;
    while (i < 11 && rpmCurve[i] < rpm) {
        i++;
    }

    if (i == 0) {
        return 0.0;
    } else if (i == 12) {
        return 1.0;
    }

    double alpha = double(rpm - rpmCurve[i - 1]) / double(rpmCurve[i] - rpmCurve[i - 1]);
    double actualPwm = lerp((i - 1) / 10.0, i / 10.0, alpha);
    return actualPwm;
}

double CoolingDevice::getCurrentHighScore() const {
    return currentHighScore;
}

bool CoolingDevice::getIsStarted() const {
    return currentSetSpeed > 0;
}

double CoolingDevice::getBuildUp() const {
    return buildUp;
}

double CoolingDevice::getCurrentSetSpeed() const {
    return currentSetSpeed;
}
