//
// Created by otto001 on 9/7/20.
//

#include "ThermalCpu.h"
#include "../utils.h"

#include <iostream>

int ThermalCpu::_getTemp() {
    int maxTemp = -1;
    for (std::string &path : tempPaths) {

        std::string inputPath = path;
        inputPath.append("_input");
        int temp = readIntFromFile(inputPath);

        if (temp > maxTemp) {
            maxTemp = temp;
        }
    }

    if (maxTemp == -1) {
        return -1;
    }
    return maxTemp/1000;
}

int ThermalCpu::_getLoad() {
    return ThermalZone::_getLoad();
}

bool ThermalCpu::load(YAML::Node node) {
    bool result = ThermalZone::load(node);
    tempPaths = readYamlField<std::vector<std::string>>(node, "zones");
    return result;
}
