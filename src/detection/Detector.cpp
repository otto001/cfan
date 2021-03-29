//
// Created by ludwig on 1/21/21.
//
#include <string>
#include <iostream>
#include <filesystem>
#include <regex>

#include "Detector.h"
#include "../utils.h"
#include "../system-utils.h"
#include "../cooling/CoolingDevice.h"
#include "../Control.h"
#include "../thermal/ThermalProbe.h"


Detector::Detector(Control *control) : control(control) {

}

std::vector<ThermalZone *> Detector::getThermalZonesFromHwmon(const std::filesystem::path& hwmonPath) {
#if WIN32
    return {};
#else
    auto hwmonName = readFile((hwmonPath / "name").string());
    rtrim(hwmonName);
    static const std::regex re("temp\\d+_input");

    std::vector<ThermalZone *> zones;

    for (const auto &entry : std::filesystem::directory_iterator(hwmonPath)) {
        auto filename = entry.path().filename().string();
        if (std::regex_match(filename, re) && entry.is_regular_file()) {

            auto baseName = filename.substr(0, filename.size() - 6);

            auto zoneLabel = readFile((hwmonPath / (baseName + "_label")).string());
            rtrim(zoneLabel);

            auto zone = new ThermalProbe();
            zone->path = hwmonPath / baseName;
            zone->name = hwmonName;
            zone->name += "_";
            zone->name += zoneLabel;

            auto temp = zone->_getTemp();
            if (temp > 0 && temp <= 120) {
                zones.push_back(zone);
            } else {
                delete zone;
            }
        }
    }
    return zones;
#endif
}


void Detector::detectThermal() {
    std::string path = "/sys/class/hwmon";

    std::vector<ThermalZone *> zones;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            auto hwmonZones = getThermalZonesFromHwmon(entry.path());
            zones.insert(zones.end(), hwmonZones.begin(), hwmonZones.end());
        }
    }
    control->thermalZones = zones;
}

void Detector::run() {
    detectThermal();
    detectCooling();
}

void Detector::detectCooling() {
#if WIN32
    return;
#else
    std::string path = "/sys/class/hwmon";
    std::vector<CoolingDevice *> devices;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            auto hwmonDevices = getCoolingDevicesFromHwmon(entry.path());
            devices.insert(devices.end(), hwmonDevices.begin(), hwmonDevices.end());
        }
    }

    resetCoolingDevicesSpeed(devices, 0.5);
    System::sleep(3000);


    auto it = devices.begin();
    while (it != devices.end()) {
        auto ignoreDevice = [=, &devices, &it]() {
            (*it)->setToSmartFanIVFanControl();
            delete *it;
            it = devices.erase(it);
        };

        auto device = *it;
        resetCoolingDevicesSpeed(devices, 0);
        System::sleep(2000);
        std::cout << "Ramping up device " << device->getPath() << " ..." << std::endl;
        device->setSpeed(1, true);

        for (int i = 0; i < 4 && device->readRpm() == 0; ++i) {
            System::sleep(500);
        }

        if (device->readRpm() == 0) {
            ignoreDevice();
            std::cout << "Ignoring device, since rpm appears to be zero." << std::endl;
            continue;
        }

        std::cout << "Please enter a name for device (leave blank to ignore device)> ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty() || name == "\n") {
            ignoreDevice();
            std::cout << "Ignoring device." << std::endl;
            continue;
        }

        device->setName(name);
        std::cout << "Set name to " << device->getName() << std::endl;

        ++it;
    }

    std::cout << "All devices have been named. Checking fan behaviour..." << std::endl;

    for (auto device : devices) {
        device->setToSmartFanIVFanControl();
    }

    System::sleep(2000);

    for (auto device : devices) {
        std::cout << std::endl << "Checking device " << device->getName() << std::endl;

        device->setToManual();
        device->setSpeed(0, true);

        bool deviceStopped = stopDevice(device);
        if (!deviceStopped) {
            std::cout << "Device won't stop. Is this device a pump? [yes/NO]> ";
            std::string isPumpAnswer;
            std::getline(std::cin, isPumpAnswer);
            device->setIsPump(isYes(isPumpAnswer));
            if (device->getIsPump()) {
                std::cout << "Device is a pump." << std::endl;
            } else {
                std::cout << "Device is a not pump." << std::endl;
            }
        }

        std::cout << "Checking start speed: ";

        // startup speed
        for (int step = 0; step <= 40; ++step) {
            std::cout << "#";
            fflush(stdout);
            device->setSpeed(step / 100.0, true);
            System::sleep(2000);
            if (device->readRpm() > 0) {
                device->minSpeed = device->startSpeed = device->getCurrentSetSpeed();
                std::cout << " OK" << std::endl;
                std::cout << "Start speed for device is " << round(100 * device->startSpeed) << "%" << std::endl;
                break;
            }
        }

        if (!device->getIsPump()) {
            stopDevice(device);
        }

        std::cout << "Measuring rpm curve: ";

        // rpm curve
        device->rpmCurve[0] = device->readRpm();
        std::cout << device->readRpm() << " - ";
        fflush(stdout);

        for (int step = 1; step <= 10; ++step) {

            device->setSpeed(step / 10.0, true);
            waitForDeviceToStabilize(device);
            int rpm = device->readRpm();
            device->rpmCurve[step] = rpm;
            std::cout << rpm;
            if (step < 10) {
                std::cout << " - ";
            }
            fflush(stdout);
        }
        std::cout << " OK" << std::endl;

        device->setToSmartFanIVFanControl();

    }

    resetCoolingDevicesSpeed(devices, 0.5);
    System::sleep(3000);
    for (auto device : devices) {
        device->setToSmartFanIVFanControl();
    }

    std::cout << "Reset all fans to SmartFanIV control" << std::endl;
    control->coolingDevices = devices;
#endif
}

std::vector<CoolingDevice *> Detector::getCoolingDevicesFromHwmon(const std::filesystem::path &path) {
#if WIN32
    return {};
#else
    static const std::regex re("pwm\\d+");

    std::vector<CoolingDevice *> devices;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        auto filename = entry.path().filename().string();
        if (std::regex_match(filename, re) && entry.is_regular_file()) {
            auto device = new CoolingDevice(control);
            device->setPath(entry.path());
            devices.push_back(device);
        }
    }

    return devices;
#endif
}

void Detector::resetCoolingDevicesSpeed(const std::vector<CoolingDevice *> &devices, const double speed) {
    for (auto device : devices) {
        device->setToManual();
        device->setSpeed(speed, true);
    }
}

bool Detector::stopDevice(CoolingDevice *device) {
    device->setSpeed(0, true);

    std::cout << "Stopping device " << device->getName() << ": ";

    for (int counter = 0; counter < 20 && device->readRpm() > 0; ++counter) {
        System::sleep(500);
        std::cout << "#";
        fflush(stdout);
    }
    if (device->readRpm() == 0) {
        for (int counter = 0; counter < 10; ++counter) {
            System::sleep(500);
            std::cout << "#";
            fflush(stdout);
        }
        std::cout << " OK" << std::endl;
        return true;
    }
    std::cout << " FAILED" << std::endl;
    return false;
}

bool Detector::waitForDeviceToStabilize(CoolingDevice *device, int timeout) {

    constexpr int bufSize = 6;
    int buf[bufSize];
    for (int counter = 0; counter < timeout ; ++counter) {
        System::sleep(500);
        int currRpm = device->readRpm();
        buf[counter%bufSize] = currRpm;

        if (counter >= bufSize) {
            int max = buf[0];
            int min = buf[0];
            for(int i=1; i<bufSize; i++) {
                if(buf[i] > max) {
                    max = buf[i];
                }
                if(buf[i] < min) {
                    min = buf[i];
                }
            }

            if (min*1.1 >= max) {
                return true;
            }
        }
    }
    return false;
}


































