//
// Created by otto001 on 9/7/20.
//

#include "CoolingDevice.h"
#include "../Control.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include "../utils.h"


CoolingDevice::CoolingDevice(Control *control) : control(control) {

}


bool CoolingDevice::init() {
    setToManual();
    return true;
}

//int CoolingDevice::getIndex() const {
//
//    std::string fileName = path.filename().string();
//    size_t last_index = fileName.find_last_not_of("0123456789");
//    std::string digits = fileName.substr(last_index + 1);
//    int result = -1;
//    try {
//        result = (int) std::stoi(digits);
//    } catch (std::invalid_argument &e) {
//        result = -1;
//    } catch (std::out_of_range &e) {
//        result = -1;
//    }
//
//    return result;
//}

bool CoolingDevice::setSpeed(double speed, bool force) {
    speed = std::min(std::max(speed, 0.0), 1.0);
    auto speedInt = (int) round(speed * 255);


    if (!isPump && !force) {
        auto minSpeedInt = (int) round(minSpeed * 255);
        auto startSpeedInt = (int) round(startSpeed * 255);

        if (speedInt > 0 && speedInt < minSpeedInt) {
            speed = minSpeed;
            speedInt = minSpeedInt;
        }
        if (speedInt >= minSpeedInt && speedInt < startSpeedInt && readRpm() == 0) {
            speed = startSpeed;
            speedInt = startSpeedInt;
        }
    }

    if (!force && currentSetSpeedInt == speedInt) {
        return true;
    }
#if WIN32
    return false;
#else
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
#endif
}

bool CoolingDevice::setToManual() {
#if WIN32
    return false;
#else
    std::string enablePath = getPwmPath().string();
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
#endif

}

int CoolingDevice::readRpm() {
#if WIN32
    return 0;
#else
    auto inputPath = getFanPath().string() + "_input";
    return readIntFromFile(inputPath);
#endif
}

bool CoolingDevice::setToQFanControl() {
#if WIN32
    return false;
#else
    auto enablePath = getPwmPath().string();
    enablePath.append("_enable");

    std::ofstream file;
    file.open(enablePath, std::ios::out | std::ios::trunc);

    if (file.is_open()) {
        file << 5;
        file.close();

        setSpeed(currentSetSpeed, true);
        return true;
    }
    std::cerr << "Failed to set mode of cooling device " << name << " to QFan!" << std::endl;
    return false;
#endif
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

    //path = readYamlField<std::string>(node, "path");
    name = readYamlField<std::string>(node, "name");


    lazinessStart = readYamlField<double>(node, "laziness-start", 60);
    lazinessStop = readYamlField<double>(node, "laziness-stop", 60);
    lazinessStart /= 100.0;
    lazinessStop /= 100.0;

    linearity = readYamlField<double>(node, "linearity", 0.0);
    linearity /= 100.0;

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


YAML::Node *CoolingDevice::writeToYamlNode() {
    auto node = new YAML::Node(YAML::NodeType::Map);
    (*node)["name"] = name;
    //(*node)["path"] = path.string();

    (*node)["is-pump"] = isPump;


    (*node)["start-speed"] = round(startSpeed*100);
    (*node)["min-speed"] = round(minSpeed*100);

    (*node)["linearity"] = round(linearity*100);

    (*node)["laziness-start"] =  round(lazinessStart*100);
    (*node)["laziness-stop"] = round(lazinessStop*100);

    (*node)["rpm-curve"] = join(rpmCurve, 11, "-");

    (*node)["thermal-zones"] = YAML::Node(YAML::NodeType::Sequence);
    for (auto zone : thermalZones) {
        (*node)["thermal-zones"].push_back(zone->getName());
    }
    return node;
}


void CoolingDevice::update() {
    checkIsResponsive();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
    getHottestZone();
#pragma clang diagnostic pop

    double deltaSeconds = double(control->getInterval()) / 1000.0;


    if (currentHighScore < 1) {
        // under idle
        buildUp -= buildUp*0.25*deltaSeconds;
    } else if (currentHighScore < 2) {
        // over idle under desired
        double target = (1 + currentHighScore - 1) * (buildUpThreshold / 10);
        buildUp += (target - buildUp) * 0.15*deltaSeconds;
    } else if (currentHighScore < 3) {
        // over desired under critical
        double target = (1 + currentHighScore - 2) * buildUpThreshold;
        buildUp += std::max((target - buildUp) * 0.5, 0.0)*deltaSeconds;
    } else {
        // critical
        buildUp = buildUpThreshold * 3;
    }

    buildUp = std::max(0.0, buildUp);

    bool started = currentSetSpeed != 0;
    if (!started && (buildUp > buildUpThreshold * lerp(1.0, 1.5, lazinessStart)) || lazinessStart == 0) {
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
    if (control->debug) {
        std::cout << name
        << ":\n\tscore: " << currentHighScore
        << "\n\tspeed: " << targetSpeed
        << "\n\trpm: " << readRpm() << std::endl;
    }
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
    int currentRpm = readRpm();

    int currentSpeedBracket = round(currentSetSpeed*10);  // speed as int between 0 and 10
    int supposedRpmLowerBound = rpmCurve[currentSpeedBracket];
    int supposedRpmUpperBound = rpmCurve[currentSpeedBracket+1];
    int supposedRpm = lerp(supposedRpmLowerBound, supposedRpmUpperBound, currentSetSpeed*10-currentSpeedBracket);


    //double actualPwmSpeed = calculateActualPwmSpeed();

    if (currentSetSpeedInt == 0 && isPump) {
        diff = 0;
    } else {
        diff = std::abs(currentRpm - supposedRpm);
    }


    if (diff > supposedRpm*0.05) {
        unresponsiveCounter++;

        if (unresponsiveCounter > 8) {
            unresponsiveCounter = 0;
            if (control->debug) {
                std::cout << name << " is deviating from speed curve. Setting pwm_mode to manual (1)..." << std::endl;
            }
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

