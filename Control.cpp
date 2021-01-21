//
// Created by otto001 on 9/7/20.
//

#include "Control.h"
#include "Table.h"
#include "utils.h"
#include "detection/Detector.h"
#include <vector>
#include <unistd.h>
#include <iostream>


bool Control::load() {
    YAML::Node config;
    try {
        config = YAML::LoadFile(configPath);
    } catch (YAML::BadFile) {
        return false;
    }

    auto thermalConfig = config["thermal"];
    auto thermalZonesConfig = thermalConfig["zones"].as<std::vector<YAML::Node>>();

    for (auto &zoneConfig : thermalZonesConfig) {
        auto zone = ThermalZone::loadZone(zoneConfig);
        if (zone) {
            thermalZones.push_back(zone);
        } else {
            std::cerr << "Could not load thermal zone '" << readYamlField<std::string>(zoneConfig, "name", "no name provided") << "'" << std::endl;
        }
    }


    auto coolingConfig = config["cooling"];
    auto coolingDevicesConfig = coolingConfig["devices"].as<std::vector<YAML::Node>>();

    for (auto &deviceConfig : coolingDevicesConfig) {
        auto device = CoolingDevice::loadDevice(deviceConfig, this);
        if (device) {
            coolingDevices.push_back(device);
        }
    }

    return true;
}

void Control::init() {
    for (auto device : coolingDevices) {
        device->init();
    }
}

[[noreturn]] void Control::run() {

    init();

    while (true) {
        auto t1 = std::chrono::high_resolution_clock::now();
        update();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        long sleepDuration = (interval*1000) - duration;

        if (sleepDuration > 0) {
            usleep(sleepDuration);
        }

    }
}


[[noreturn]] void Control::curses() {
    while (true) {
        auto t1 = std::chrono::high_resolution_clock::now();
        update();
        writeToStdout();
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        long sleepDuration = (interval*1000) - duration;

        if (sleepDuration > 0) {
            usleep(sleepDuration);
        }

    }
}

void Control::detect() {
    Detector detector = Detector(this);
    detector.run();
}

void Control::update() {

    for (auto zone : thermalZones) {
        zone->update();
    }
    for (auto device : coolingDevices) {
        device->update();
    }
}

ThermalZone *Control::getThermalZone(const std::string& name) {
    for (auto zone : thermalZones) {
        if (zone->getName() == name) {
            return zone;
        }
    }
    return nullptr;
}

void Control::writeToStdout() {
    static Table coolingTable(this);
    coolingTable.refreshTable();
}

const std::vector<ThermalZone *> &Control::getThermalZones() const {
    return thermalZones;
}

const std::vector<CoolingDevice *> &Control::getCoolingDevices() const {
    return coolingDevices;
}

int Control::getInterval() const {
    return interval;
}



