//
// Created by ludwig on 24.01.2021.
//

#ifndef WINFAN_CPU_H
#define WINFAN_CPU_H


#include <cstdint>
#include "../Device.h"

class CPU : public Device {
public:
    CPU(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData);

    virtual bool readCpuCoreTemp(int32_t* temp) {return false;};
};


#endif //WINFAN_CPU_H
