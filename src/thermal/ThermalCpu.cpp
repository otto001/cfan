//
// Created by otto001 on 9/7/20.
//

#include "ThermalCpu.h"
#include "../utils.h"

#include <iostream>

#if WIN32
#include <winfan/winfan.h>
#else
#include "../linux/linux-utils.h"
#endif

int ThermalCpu::_getTemp() {
#if WIN32
    int32_t result;
    if (WinFan::readCpuCoreTemp(&result)) {
        return result;
    }
    std::cerr << "Failed to read temperature of thermal zone (cpu) " << name << std::endl;
    return 100;
#else
    return ThermalZone::_getTemp();
#endif
}

int ThermalCpu::_getLoad() {
    return ThermalZone::_getLoad();
}

bool ThermalCpu::load(YAML::Node node) {
    auto result = ThermalZone::load(node);
#if !WIN32
    if (getHwmonPathByName(path, "k10temp")) {
        path /= "temp2";
    } else {
        return getHwmonPathByName(path, "coretemp");
    }
#endif
    return result;
}
