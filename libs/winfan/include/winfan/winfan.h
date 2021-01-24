//
// Created by ludwig on 23.01.2021.
//

#ifndef CFAN_WINFAN_H
#define CFAN_WINFAN_H

namespace WinFan {
    extern long long interval;
    bool init();
    bool readFanRpm(uint8_t fanIndex, int32_t* result, bool force=false);
}



#endif //CFAN_WINFAN_H
