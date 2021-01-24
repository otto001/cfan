//
// Created by ludwig on 23.01.2021.
//

#include "pch.h"
#include "include/winfan/winfan.h"


#include <iostream>

#include <iostream>
#include "OlsDll.h"
#include "Service.h"
#include "lpcIo/LpcIo.h"
#include "devices/Devices.h"
#define DRIVER_NAME "WinRing0_1_2_0"
#define DRIVER_NAME_W L"WinRing0_1_2_0"


Devices* smBios;
long long WinFan::interval = 500;


bool WinFan::init() {
    OlsDll::init();
    smBios = new Devices();
    smBios->init();
    return true;
}


bool WinFan::close() {
    OlsDll::close();
    return false;
}

SuperIo* getSuperIO() {
    if (!smBios) return nullptr;
    auto mainBoard = smBios->getMainBoard();
    if (!mainBoard) return nullptr;
    auto superIo = mainBoard->getSuperIo();
    return superIo;
}

bool WinFan::readFanRpm(uint8_t fanIndex, int32_t* result, bool force) {
    auto superIo = getSuperIO();
    if (!superIo) return false;
    superIo->timedUpdate(force);
    if (fanIndex >= superIo->getFans().size()) return false;

    auto rpm = (int32_t) superIo->getFans()[fanIndex];

    if (result) {
        *result = rpm;
    }

    return true;
}

bool WinFan::setFanSpeed(uint8_t fanIndex, int32_t speed, bool force) {
    auto superIo = getSuperIO();
    if (!superIo) return false;
    superIo->timedUpdate(force);
    if (fanIndex >= superIo->getFans().size()) return false;
    superIo->setFanSpeed(fanIndex, speed);
    return true;
}

bool WinFan::setFanControlMode(uint8_t fanIndex, int32_t mode, bool force) {
    auto superIo = getSuperIO();
    if (!superIo) return false;
    superIo->timedUpdate(force);
    if (fanIndex >= superIo->getFans().size()) return false;
    superIo->setFanControlMode(fanIndex, mode);
    return true;
}

bool WinFan::readCpuCoreTemp(int32_t *result, bool force) {
    if (!smBios) return false;
    auto cpu = smBios->getCpu();
    if (!cpu) return false;
    return cpu->readCpuCoreTemp(result);
}






