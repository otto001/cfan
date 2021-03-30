//
// Created by ludwig on 23.01.2021.
//

#ifndef CFAN_WINFAN_H
#define CFAN_WINFAN_H

#include <stdint.h>

namespace WinFan {
    extern long long interval;
    bool init();
    bool close();

    bool readCpuCoreTemp(int32_t* result, bool force=false);

    bool readTemperature(uint8_t tempIndex, int32_t* result, bool force=false);

    bool readFanRpm(uint8_t fanIndex, int32_t* result, bool force=false);
    bool setFanSpeed(uint8_t fanIndex, int32_t speed, bool force=false);
    bool setFanControlMode(uint8_t fanIndex, int32_t mode, bool force=false);
}



#endif //CFAN_WINFAN_H
