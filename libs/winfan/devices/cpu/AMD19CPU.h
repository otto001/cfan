//
// Created by ludwig on 24.01.2021.
//

#ifndef WINFAN_AMD19CPU_H
#define WINFAN_AMD19CPU_H
#include <Windows.h>
#include <cstdint>
#include "CPU.h"

class AMD19CPU : public CPU {

public:
    AMD19CPU(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData);

    bool readCpuCoreTemp(int32_t* temp);
protected:
    const DWORD FAMILY_17H_M01H_THM_TCON_TEMP = 0x00059800;
    const DWORD FAMILY_17H_M01H_THM_TCON_TEMP_RANGE_SEL = 0x80000;
    static bool readSmnRegister(DWORD address, DWORD* value);

};


#endif //WINFAN_AMD19CPU_H
