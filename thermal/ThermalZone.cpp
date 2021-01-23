//
// Created by otto001 on 9/7/20.
//

#include <fstream>
#include "ThermalZone.h"
#include "ThermalCpu.h"
#include "../utils.h"
#include "ThermalNvidiaGpu.h"

const std::string &ThermalZone::getName() const {
    return name;
}

int ThermalZone::_getTemp() {
    auto inputPath = path.string();
    inputPath.append("_input");
    int result = readIntFromFile(inputPath);
    if (result == -1) {
        return -1;
    }
    return result/1000;
}

int ThermalZone::_getLoad() {
    return -1;
}

int ThermalZone::getTemp() {
    if (tempCache < 0) {
        tempCache = _getTemp();
    }
    return tempCache;
}

int ThermalZone::getLoad() {
    if (loadCache < 0) {
        loadCache = _getLoad();
    }
    return loadCache;
}

double ThermalZone::getScore() {
    auto temp = (double) getTemp();
    if (temp <= idle) {
        return temp / idle;
    } else if (temp <= desired) {
        return 1 + (temp - idle) / (desired - idle);
    } else if (temp <= critical) {
        return 2 + (temp - desired) / (critical - desired);
    }
    return 3;
}

bool ThermalZone::load(YAML::Node node) {
    idle = readYamlField<int>(node, "idle", 50);
    desired = readYamlField<int>(node, "desired", 60);
    critical = readYamlField<int>(node, "critical", 80);

    path = readYamlField<std::string>(node, "path", "");

    name = readYamlField<std::string>(node, "name");

    return true;
}

ThermalZone *ThermalZone::loadZone(YAML::Node& node) {
    auto className = readYamlField<std::string>(node, "class", "ThermalZone");

    if (className.size() < 7 || className.substr(0, 7) != "Thermal") {
        className = "Thermal" + className;
    }
    ThermalZone *zone = nullptr;

    if (className == "ThermalZone") {
        zone = new ThermalZone();
    } else if (className == "ThermalCpu") {
        zone = new ThermalCpu();
    } else if (className == "ThermalNvidiaGpu") {
        zone = new ThermalNvidiaGpu();
    }

    if (zone) {
        zone->load(node);
    }

    return zone;
}

void ThermalZone::update() {
    loadCache = -1;
    tempCache = -1;
}

YAML::Node *ThermalZone::writeToYamlNode() {
    auto node = new YAML::Node(YAML::NodeType::Map);
    (*node)["name"] = name;
    (*node)["path"] = path.string();

    (*node)["idle"] = idle;
    (*node)["desired"] = desired;
    (*node)["critical"] = critical;
    return node;
}

