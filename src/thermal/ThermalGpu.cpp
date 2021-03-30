//
// Created by otto001 on 9/7/20.
//

#include "ThermalGpu.h"
#include "../utils.h"

#include <iostream>

#if WIN32
#include <winfan/winfan.h>
#else
#include "../linux/linux-utils.h"
#endif

int ThermalGpu::_getTemp() {
#if WIN32

    return 100;
#else
    return ThermalZone::_getTemp();
#endif
}

int ThermalGpu::_getLoad() {
    return ThermalZone::_getLoad();
}

bool ThermalGpu::load(YAML::Node& node) {
    auto result = ThermalZone::load(node);
#if !WIN32
    if (result) {
        if (getHwmonPathByName(path, "amdgpu")) {
            path /= "temp2";
        } else {
            return false;
        }
    }
#endif
    return result;
}
