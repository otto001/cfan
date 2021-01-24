#include "../../../pch.h"
#include "NCT6775.h"
#include "../../../OlsDll.h"
#include "../../../lpcIo/LpcIo.h"
#include <iostream>

/*

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.

  Copyright (C) 2010-2020 Michael M�ller <mmoeller@openhardwaremonitor.org>
    Copyright (C) 2015 Dawid Gan <deveee@gmail.com>

*/

NCT6775::NCT6775(Chip _chip, uint8_t _revision, uint16_t _port, const LpcIoPort* _lpcPort) : SuperIo(_chip, _revision, _port, _lpcPort) {
    restoreDefaultFanControlRequired = std::vector<bool>(7, false);
    initialFanControlMode = std::vector<uint8_t>(7, 0);
    initialFanPwmCommand = std::vector<uint8_t>(7, 0);


    if (chip == Chip::NCT610X) {
        VENDOR_ID_HIGH_REGISTER = 0x80FE;
        VENDOR_ID_LOW_REGISTER = 0x00FE;

        FAN_PWM_OUT_REG = { 0x04A, 0x04B, 0x04C };
        FAN_PWM_COMMAND_REG = { 0x119, 0x129, 0x139 };
        FAN_CONTROL_MODE_REG = { 0x113, 0x123, 0x133 };

        vBatMonitorControlRegister = 0x0318;
    }
    else {
        VENDOR_ID_HIGH_REGISTER = 0x804F;
        VENDOR_ID_LOW_REGISTER = 0x004F;

        FAN_PWM_OUT_REG = {
          0x001, 0x003, 0x011, 0x013, 0x015, 0x017, 0x029 };
        FAN_PWM_COMMAND_REG = {
          0x109, 0x209, 0x309, 0x809, 0x909, 0xA09, 0xB09 };
        FAN_CONTROL_MODE_REG = {
          0x102, 0x202, 0x302, 0x802, 0x902, 0xA02, 0xB02 };

        vBatMonitorControlRegister = 0x005D;
    }


    isNuvotonVendor = getIsNuvotonVendor();

    if (!isNuvotonVendor) {
        return;
    }

    switch (chip) {
    case Chip::NCT6771F:
    case Chip::NCT6776F:
        if (chip == Chip::NCT6771F) {
            fans = {0, 0, 0, 0};

            // min RPM value with 16-bit fan counter
            minFanRPM = (int)(1.35e6 / 0xFFFF);

            temperaturesSource = {
              (uint8_t)SourceNCT6771F::PECI_0,
              (uint8_t)SourceNCT6771F::CPUTIN,
              (uint8_t)SourceNCT6771F::AUXTIN,
              (uint8_t)SourceNCT6771F::SYSTIN
            };
        }
        else {
            fans = { 0, 0, 0, 0, 0 };

            // min RPM value with 13-bit fan counter
            minFanRPM = (int)(1.35e6 / 0x1FFF);

            temperaturesSource = {
              (uint8_t)SourceNCT6776F::PECI_0,
              (uint8_t)SourceNCT6776F::CPUTIN,
              (uint8_t)SourceNCT6776F::AUXTIN,
              (uint8_t)SourceNCT6776F::SYSTIN
            };
        }
        fanRpmBaseRegister = { 0x656, 0x658, 0x65A, 0x65C, 0x65E };

        controls = {0, 0, 0};

        voltages = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        voltageRegisters =  { 0x020, 0x021, 0x022, 0x023, 0x024, 0x025, 0x026, 0x550, 0x551 };
        voltageVBatRegister = 0x551;

        temperatures = {0, 0, 0, 0};
        temperatureRegister =  { 0x027, 0x073, 0x075, 0x077, 0x150, 0x250, 0x62B, 0x62C, 0x62D };
        temperatureHalfRegister = { 0, 0x074, 0x076, 0x078, 0x151, 0x251, 0x62E, 0x62E, 0x62E };
        temperatureHalfBit = { -1, 7, 7, 7, 7, 7, 0, 1, 2 };
        temperatureSourceRegister =  { 0x621, 0x100, 0x200, 0x300, 0x622, 0x623, 0x624, 0x625, 0x626 };

        alternateTemperatureRegister = { nullptr, nullptr, nullptr, nullptr };
        break;

    case Chip::NCT6779D:
    case Chip::NCT6791D:
    case Chip::NCT6792D:
    case Chip::NCT6792DA:
    case Chip::NCT6793D:
    case Chip::NCT6795D:
    case Chip::NCT6796D:
    case Chip::NCT6796DR:
    case Chip::NCT6797D:
    case Chip::NCT6798D:
        switch (chip) {
        case Chip::NCT6791D:
        case Chip::NCT6792D:
        case Chip::NCT6792DA:
        case Chip::NCT6793D:
        case Chip::NCT6795D:
            fans = {0, 0, 0, 0, 0, 0};
            controls = {0, 0, 0, 0, 0, 0};
            break;
        case Chip::NCT6796D:
        case Chip::NCT6796DR:
        case Chip::NCT6797D:
        case Chip::NCT6798D:
            fans = {0, 0, 0, 0, 0, 0, 0};
            controls = {0, 0, 0, 0, 0, 0, 0};
            break;
        default:
            fans = {0, 0, 0, 0, 0};
            controls = {0, 0, 0, 0, 0};
            break;
        }

        fanCountRegister = { 0x4B0, 0x4B2, 0x4B4, 0x4B6, 0x4B8, 0x4BA, 0x4CC };

        // max value for 13-bit fan counter
        maxFanCount = 0x1FFF;

        // min value that could be transfered to 16-bit RPM registers
        minFanCount = 0x15;

        voltages = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        voltageRegisters = { 0x480, 0x481, 0x482, 0x483, 0x484, 0x485, 0x486, 0x487, 0x488, 0x489, 0x48A, 0x48B, 0x48C, 0x48D, 0x48E };
        voltageVBatRegister = 0x488;

        temperatures = {0, 0, 0, 0, 0, 0, 0};
        temperaturesSource = {
          (uint8_t)SourceNCT67XXD::PECI_0,
          (uint8_t)SourceNCT67XXD::CPUTIN,
          (uint8_t)SourceNCT67XXD::SYSTIN,
          (uint8_t)SourceNCT67XXD::AUXTIN0,
          (uint8_t)SourceNCT67XXD::AUXTIN1,
          (uint8_t)SourceNCT67XXD::AUXTIN2,
          (uint8_t)SourceNCT67XXD::AUXTIN3
        };

        temperatureRegister = { 0x027, 0x073, 0x075, 0x077, 0x079, 0x07B, 0x150 };
        temperatureHalfRegister = { 0, 0x074, 0x076, 0x078, 0x07A, 0x07C, 0x151 };
        temperatureHalfBit = { -1, 7, 7, 7, 7, 7, 7 };
        temperatureSourceRegister = { 0x621, 0x100, 0x200, 0x300, 0x800, 0x900, 0x622 };

        alternateTemperatureRegister = {nullptr, new uint16_t(0x491), new uint16_t(0x490), new uint16_t(0x492), new uint16_t(0x493), new uint16_t(0x494), new uint16_t(0x495) };

        break;
    case Chip::NCT610X:

        fans = {0, 0, 0};
        controls = {0, 0, 0};

        fanRpmBaseRegister = { 0x030, 0x032, 0x034 };

        // min value RPM value with 13-bit fan counter
        minFanRPM = (int)(1.35e6 / 0x1FFF);

        voltages = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        voltageRegisters = 
        { 0x300, 0x301, 0x302, 0x303, 0x304, 0x305, 0x307, 0x308, 0x309 };
        voltageVBatRegister = 0x308;

        temperatures = {0, 0, 0, 0};
        temperaturesSource = {
          (uint8_t)SourceNCT610X::PECI_0,
          (uint8_t)SourceNCT610X::SYSTIN,
          (uint8_t)SourceNCT610X::CPUTIN,
          (uint8_t)SourceNCT610X::AUXTIN
        };

        temperatureRegister = { 0x027, 0x018, 0x019, 0x01A };
        temperatureHalfRegister =  { 0, 0x01B, 0x11B, 0x21B };
        temperatureHalfBit =  { -1, 7, 7, 7 };
        temperatureSourceRegister =  { 0x621, 0x100, 0x200, 0x300 };

        alternateTemperatureRegister = {nullptr, new uint16_t(0x018), new uint16_t(0x019), new uint16_t(0x01A) };

        break;
    }

}

uint8_t NCT6775::readByte(uint16_t address) {
    auto bank = (uint8_t)(address >> 8);
    auto reg = (uint8_t)(address & 0xFF);
    
    OlsDll::writeIoPortByte(port + ADDRESS_REGISTER_OFFSET, BANK_SELECT_REGISTER);
    OlsDll::writeIoPortByte(port + DATA_REGISTER_OFFSET, bank);
    OlsDll::writeIoPortByte(port + ADDRESS_REGISTER_OFFSET, reg);
    uint8_t result;
    OlsDll::readIoPortByte(port + DATA_REGISTER_OFFSET, &result);
    return result;
}

void NCT6775::writeByte(uint16_t address, uint8_t value) {
    auto bank = (uint8_t)(address >> 8);
    auto reg = (uint8_t)(address & 0xFF);
    OlsDll::writeIoPortByte(port + ADDRESS_REGISTER_OFFSET, BANK_SELECT_REGISTER);
    OlsDll::writeIoPortByte(port + DATA_REGISTER_OFFSET, bank);
    OlsDll::writeIoPortByte(port + ADDRESS_REGISTER_OFFSET, reg);
    OlsDll::writeIoPortByte(port + DATA_REGISTER_OFFSET, value);
}


   

bool NCT6775::getIsNuvotonVendor() {
  return ((readByte(VENDOR_ID_HIGH_REGISTER) << 8) |
      readByte(VENDOR_ID_LOW_REGISTER)) == NUVOTON_VENDOR_ID;
}


void NCT6775::saveDefaultFanControl(int index) {
    if (!restoreDefaultFanControlRequired[index]) {
        initialFanControlMode[index] = readByte(FAN_CONTROL_MODE_REG[index]);
        initialFanPwmCommand[index] = readByte(FAN_PWM_COMMAND_REG[index]);
        restoreDefaultFanControlRequired[index] = true;
    }
}

void NCT6775::restoreDefaultFanControl(int index) {
    if (restoreDefaultFanControlRequired[index]) {
        writeByte(FAN_CONTROL_MODE_REG[index], initialFanControlMode[index]);
        writeByte(FAN_PWM_COMMAND_REG[index], initialFanPwmCommand[index]);
        restoreDefaultFanControlRequired[index] = false;
    }
}

void NCT6775::setFanControlMode(int index, uint8_t value) {
    if (!isNuvotonVendor) {
        return;
    }

    if (index < 0 || index >= controls.size()) {
        return;
    }

    if (!OlsDll::isaBusMutexWait(10)) {
        return;
    }

    saveDefaultFanControl(index);

    // set manual mode
    writeByte(FAN_CONTROL_MODE_REG[index], 0);

    OlsDll::isaBusMutexRelease();
}

void NCT6775::setFanSpeed(int index, uint8_t value) {
    if (!isNuvotonVendor) {
        return;
    }

    if (index < 0 || index >= controls.size()) {
        return;
    }

    if (!OlsDll::isaBusMutexWait(10)) {
        return;
    }

    // set output value
    writeByte(FAN_PWM_COMMAND_REG[index], value);

    OlsDll::isaBusMutexRelease();
}

void NCT6775::disableIOSpaceLock() {
    if (chip != Chip::NCT6791D &&
        chip != Chip::NCT6792D &&
        chip != Chip::NCT6792DA &&
        chip != Chip::NCT6793D &&
        chip != Chip::NCT6795D &&
        chip != Chip::NCT6796D &&
        chip != Chip::NCT6796DR &&
        chip != Chip::NCT6797D &&
        chip != Chip::NCT6798D)
        return;

    // the lock is disabled already if the vendor ID can be read
    if (getIsNuvotonVendor())
        return;

    lpcPort->detectWinboundFintekEnter();
    lpcPort->nuvotonDisableIOSpaceLock();
    lpcPort->detectWinboundFintekExit();
}

void NCT6775::update() {
    if (!isNuvotonVendor)
        return;

    if (!OlsDll::isaBusMutexWait(10))
        return;

    disableIOSpaceLock();

    for (int i = 0; i < voltages.size(); i++) {
        float value = 0.008f * readByte(voltageRegisters[i]);
        bool valid = value > 0;

        // check if battery voltage monitor is enabled
        if (valid && voltageRegisters[i] == voltageVBatRegister) {
            valid = (readByte(vBatMonitorControlRegister) & 0x01) > 0;
        }

        voltages[i] = valid ? value : -1;
    }

    int temperatureSourceMask = 0;
    for (int i = temperatureRegister.size() - 1; i >= 0; i--) {

        int value = ((int8_t)readByte(temperatureRegister[i])) << 1;
        if (temperatureHalfBit[i] > 0) {
            value |= ((readByte(temperatureHalfRegister[i]) >>
            temperatureHalfBit[i]) & 0x1);
        }

        uint8_t source = readByte(temperatureSourceRegister[i]);
        temperatureSourceMask |= 1 << source;

        float temperature = 0.5f * value;
        if (temperature > 125 || temperature < -55) {
            temperature = -1;
        }

        for (int j = 0; j < temperatures.size(); j++) {
            if (temperaturesSource[j] == source) {
                temperatures[j] = temperature;
            }
        }
    }


    for (int i = 0; i < alternateTemperatureRegister.size(); i++) {
        if (!alternateTemperatureRegister[i])
            continue;

        if ((temperatureSourceMask & (1 << temperaturesSource[i])) > 0)
            continue;

        float temperature = (int8_t) readByte(*alternateTemperatureRegister[i]);

        if (temperature > 125 || temperature < -55) {
            temperature = -1;
        }

        temperatures[i] = temperature;
    }

    for (int i = 0; i < fans.size() && i < fanCountRegister.size(); i++) {
        if (fanCountRegister[i] != 0) {
            uint8_t high = readByte(fanCountRegister[i]);
            uint8_t low = readByte((uint16_t)(fanCountRegister[i] + 1));
            int count = (high << 5) | (low & 0x1F);
            if (count < maxFanCount) {
                if (count >= minFanCount) {
                    fans[i] = 1.35e6f / count;
                }
                else {
                    fans[i] = -1;
                }
            } else {
                fans[i] = 0;
            }
        } else {
            uint8_t high = readByte(fanRpmBaseRegister[i]);
            uint8_t low = readByte((uint16_t)(fanRpmBaseRegister[i] + 1));
            int value = (high << 8) | low;

            fans[i] = value > minFanRPM ? value : 0;
        }
    }

    for (int i = 0; i < controls.size(); i++) {
      int value = readByte(FAN_PWM_OUT_REG[i]);
      controls[i] = value / 2.55f;
    }

    OlsDll::isaBusMutexRelease();
}
