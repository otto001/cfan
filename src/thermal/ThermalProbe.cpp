//
// Created by root on 3/29/21.
//

#include <winfan/winfan.h>
#include "ThermalProbe.h"
#include "../utils.h"

#if WIN32
#endif


int ThermalProbe::_getTemp() {
#if WIN32
    int32_t result;
    WinFan::readTemperature(index, &result);
    return result;
#else
    ThermalZone::_getTemp()
#endif
}

bool ThermalProbe::load(YAML::Node node) {
    auto result = ThermalZone::load(node);
    if (result) {
#if WIN32
        index = readYamlField<uint8_t>(node, "index");
#else
        auto index = readYamlField<uint8_t>(node, "index");
        auto hwmonName = readYamlField<std::string>(node, "hwmon-name");
        if (!getHwmonPathByName(path, hwmonName)) {
            return false;
        }
        path /= "temp" + std::to_string(index);
#endif

        return true;
    }
    return false;
}

YAML::Node *ThermalProbe::writeToYamlNode() {
    auto node = ThermalZone::writeToYamlNode();
    if (node) {
#if WIN32
#else
#endif

        return node;
    }
    return nullptr;
}
