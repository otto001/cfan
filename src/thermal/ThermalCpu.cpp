//
// Created by otto001 on 9/7/20.
//

#include "ThermalCpu.h"
#include "../utils.h"

#include <iostream>
#include <winfan/winfan.h>

int ThermalCpu::_getTemp() {
#if WIN32
    int32_t result;
    if (WinFan::readCpuCoreTemp(&result)) {
        return result;
    }
    return 100;
#else
#endif
}

int ThermalCpu::_getLoad() {
    return ThermalZone::_getLoad();
}

