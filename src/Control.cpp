//
// Created by otto001 on 9/7/20.
//

#include "Control.h"
//#include "Table.h"
#include "utils.h"
#include "system-utils.h"
#include "detection/Detector.h"
#include <vector>
#include <iostream>


bool Control::load() {
    try {
        YAML::Node config;
        config = YAML::LoadFile(configPath);

        auto thermalConfig = config["thermal"];
        auto thermalZonesConfig = thermalConfig["zones"].as<std::vector<YAML::Node>>();

        for (auto &zoneConfig : thermalZonesConfig) {
            auto zone = ThermalZone::loadZone(zoneConfig);
            if (zone) {
                thermalZones.push_back(zone);
            } else {
                std::cerr << "Could not load thermal zone '"
                          << readYamlField<std::string>(zoneConfig, "name", "no name readable")
                          << "'" << std::endl;
            }
        }


        auto coolingConfig = config["cooling"];
        auto coolingDevicesConfig = coolingConfig["devices"].as<std::vector<YAML::Node>>();

        for (auto &deviceConfig : coolingDevicesConfig) {
            auto device = CoolingDevice::loadDevice(deviceConfig, this);
            if (device) {
                coolingDevices.push_back(device);
            } else {
                std::cerr << "Could not load cooling device '"
                          << readYamlField<std::string>(deviceConfig, "name", "no name readable")
                          << "'" << std::endl;
            }
        }

        return true;
    } catch (YAML::BadFile &) {
        return false;
    } catch (LoadingException &) {
        return false;
    } catch (YAML::Exception &) {
        return false;
    }

}


bool Control::save() {
    YAML::Node config(YAML::NodeType::Map);

    YAML::Node coolingNodes(YAML::NodeType::Sequence);
    for (auto device : coolingDevices) {
        auto node = device->writeToYamlNode();
        coolingNodes.push_back(*node);
    }
    config["cooling"]["devices"] = coolingNodes;

    YAML::Node thermalNodes(YAML::NodeType::Sequence);
    for (auto zone : thermalZones) {
        auto node = zone->writeToYamlNode();
        thermalNodes.push_back(*node);
    }
    config["thermal"]["zones"] = thermalNodes;

    std::ofstream file;
    file.open(configPath, std::ios::out | std::ios::trunc);

    if (file.is_open()) {
        file << config;
        file.close();
        std::cout << "Saved config to " << configPath;
        return true;
    }
    return false;
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

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        auto sleepDuration = interval - duration;

        if (sleepDuration > 0) {
            System::sleep(sleepDuration);
        }

    }
}


[[noreturn]] void Control::curses() {
    while (true) {
        auto t1 = std::chrono::high_resolution_clock::now();
        update();
        writeToStdout();
        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
        long sleepDuration = interval - duration;

        if (sleepDuration > 0) {
            System::sleep(sleepDuration);
        }

    }
}

void Control::detect() {
    Detector detector = Detector(this);
    detector.run();
    save();
}

void Control::update() {

    for (auto zone : thermalZones) {
        zone->update();
    }
    for (auto device : coolingDevices) {
        device->update();
    }
}

ThermalZone *Control::getThermalZone(const std::string &name) {
    for (auto zone : thermalZones) {
        if (zone->getName() == name) {
            return zone;
        }
    }
    return nullptr;
}

void Control::writeToStdout() {
    // static Table coolingTable(this);
    // coolingTable.refreshTable();
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

void Control::setFansToSmartFanIV() {
    for (auto device : coolingDevices) {
        device->setToSmartFanIVFanControl();
    }
}



