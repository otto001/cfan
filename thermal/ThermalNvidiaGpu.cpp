//
// Created by root on 9/7/20.
//

#include "ThermalNvidiaGpu.h"
#include "../utils.h"

int ThermalNvidiaGpu::_getLoad() {
    readSmi();
    return tempCache;
}

int ThermalNvidiaGpu::_getTemp() {
    readSmi();
    return tempCache;
}

void ThermalNvidiaGpu::readSmi() {
    std::string result = exec("nvidia-smi --query-gpu=temperature.gpu,utilization.gpu --format=csv,noheader");

    auto firstLineSplit = result.find_first_of(", ");
    auto firstLineEnd = result.find_first_of('\n');

    auto temp = result.substr(0, firstLineSplit);
    auto load = result.substr(firstLineSplit+2, firstLineEnd-firstLineSplit-4);

    tempCache = parseInt(temp);
    loadCache = parseInt(load);
}
