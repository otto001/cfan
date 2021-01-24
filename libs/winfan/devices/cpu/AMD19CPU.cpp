//
// Created by ludwig on 24.01.2021.
//

#include <cmath>
#include "AMD19CPU.h"
#include "../../OlsDll.h"

bool AMD19CPU::readSmnRegister(DWORD address, DWORD* value) {
    if (!OlsDll::writePciConfigDword(0, 0x60, address)) {
        *value = 0;
        return false;
    }
    return OlsDll::readPciConfigDword(0, 0x64, value);
}

bool AMD19CPU::readCpuCoreTemp(int32_t *temp) {
    if (OlsDll::pciBusMutexWait(10)) {

        DWORD value;
        if (readSmnRegister(FAMILY_17H_M01H_THM_TCON_TEMP, &value)) {
            OlsDll::pciBusMutexRelease();
            float temperature = (float) ((value >> 21) & 0x7FF) / 8.0f;
            if ((value & FAMILY_17H_M01H_THM_TCON_TEMP_RANGE_SEL) != 0) {
                temperature -= 49;
            }
            *temp = (int32_t) round(temperature);
            return true;
        }
        OlsDll::pciBusMutexRelease();
    }
    return false;
}

AMD19CPU::AMD19CPU(uint8_t type, uint16_t handle, std::vector<uint8_t> &data, std::vector<std::string> &stringData) : CPU(type,
                                                                                                                             handle,
                                                                                                                             data,
                                                                                                                             stringData){

}
