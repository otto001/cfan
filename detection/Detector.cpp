//
// Created by ludwig on 1/21/21.
//
#include <string>
#include <iostream>
#include <filesystem>
#include <unistd.h>

#include "Detector.h"
#include "../utils.h"
#include "../CoolingDevice.h"


Detector::Detector(Control *control) : control(control) {

}

void Detector::detectThermalHwmon(std::filesystem::path path) {
    auto name = readFile(path / "name");
    std::cout << name << std::endl;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().filename().string().rfind("temp", 0) == 0 && entry.is_regular_file()) {
            std::cout << entry.path().string() << std::endl;
        }

    }
}


void Detector::detectThermal() {
    std::string path = "/sys/class/hwmon";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            detectThermalHwmon(entry.path());
        }
    }
}

void Detector::run() {
    detectCooling();
}

void Detector::detectCooling() {
    std::string path = "/sys/class/hwmon";
    std::vector<CoolingDevice *> devices;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            auto hwmonDevices = getCoolingDevicesFromHwmon(entry.path());
            devices.insert(devices.end(), hwmonDevices.begin(), hwmonDevices.end());
        }
    }

    resetCoolingDevicesSpeed(devices, 0.5);
    usleep(SEC_TO_MICROSEC(3));


    auto it = devices.begin();
    while (it != devices.end()) {
        auto ignoreDevice = [=, &devices, &it]() {
            it = devices.erase(it);
        };

        auto device = *it;
        resetCoolingDevicesSpeed(devices, 0);
        usleep(SEC_TO_MICROSEC(2));
        std::cout << "Ramping up device " << device->getPath() << " ..." << std::endl;
        device->setSpeed(1, true);
        usleep(SEC_TO_MICROSEC(2));

        if (device->readRpm() == 0) {
            ignoreDevice();
            std::cout << "Ignoring device, since rpm appears to be zero."  << std::endl;
            continue;
        }

        std::cout << "Please enter a name for device (leave blank to ignore device)> ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty() || name == "\n") {
            ignoreDevice();
            std::cout << "Ignoring device."  << std::endl;
            continue;
        }

        device->setName(name);
        std::cout << "Set name to " << device->getName() << std::endl;

        ++it;
    }

    std::cout << "All devices have been named. Checking fan behaviour..."  << std::endl;


    resetCoolingDevicesSpeed(devices, 0.5);
    usleep(SEC_TO_MICROSEC(2));

    for (auto device : devices) {
        device->setSpeed(0, true);

        auto stopDevice = [=, &device]() {
            device->setSpeed(0, true);

            std::cout << "Stopping device " << device->getName() << ": ";

            for (int counter = 0; counter < 20 && device->readRpm() > 0; ++counter) {
                usleep(SEC_TO_MICROSEC(0.5));
                std::cout << "#";
                fflush(stdout);
            }
            if (device->readRpm() == 0) {
                for (int counter = 0; counter < 10; ++counter) {
                    usleep(SEC_TO_MICROSEC(0.5));
                    std::cout << "#";
                    fflush(stdout);
                }
                std::cout << " OK" << std::endl;
            }
        };

        stopDevice();
        if (device->readRpm() > 0) {
            std::cout << std::endl << "Device won't stop. Is this device a pump? [yes/NO]> ";
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
        usleep(SEC_TO_MICROSEC(2));

        // startup speed
        for (int step = 1; step <= 40; ++step) {
            std::cout << "#";
            fflush(stdout);
            device->setSpeed(step/100.0, true);
            usleep(SEC_TO_MICROSEC(1.5));
            if (device->readRpm() > 0) {
                device->startSpeed = device->getCurrentSetSpeed();
                std::cout << " OK" << std::endl;
                std::cout << "Start speed for device is " << round(100*device->startSpeed) << "%" << std::endl;
                break;
            }
        }

        stopDevice();

        std::cout << "Measuring rpm curve: ";

        // rpm curve
        device->rpmCurve[0] = 0;
        std::cout << "0 - ";

        for (int step = 1; step <= 10; ++step) {

            device->setSpeed(step/10.0, true);
            usleep(SEC_TO_MICROSEC(2));
            int rmp = device->readRpm();
            device->rpmCurve[step+1] = rmp;

            std::cout << rmp;
            if (step < 10) {
                std::cout << " - ";
            }
            fflush(stdout);
        }
        std::cout << " OK" << std::endl;

        device->setSpeed(0.5, true);

    }

    resetCoolingDevicesSpeed(devices, 0.5);
    usleep(SEC_TO_MICROSEC(3));
    for (auto device : devices) {
        device->setToQFanControl();
    }

    std::cout << "Reset all fans to QFan control" << std::endl;

}

std::vector<CoolingDevice *> Detector::getCoolingDevicesFromHwmon(std::filesystem::path path) {
    auto name = readFile(path / "name");
    std::cout << name << std::endl;

    std::vector<CoolingDevice *> devices;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        auto filename = entry.path().filename().string();
        if (filename.size() == 4 && filename.rfind("pwm", 0) == 0 && entry.is_regular_file()) {
            //detectCoolingDevice(entry.path());
            auto device = new CoolingDevice(control);
            device->setPath(entry.path());
            devices.push_back(device);
        }
    }

    return devices;
}

void Detector::resetCoolingDevicesSpeed(const std::vector<CoolingDevice *> &devices, const double speed) {
    for (auto device : devices) {
        device->setToManual();
        device->setSpeed(speed, true);
    }
}


































