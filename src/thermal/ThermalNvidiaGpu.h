//
// Created by root on 9/7/20.
//

#ifndef CFAN_THERMALNVIDIAGPU_H
#define CFAN_THERMALNVIDIAGPU_H


#include "ThermalZone.h"

class ThermalNvidiaGpu  : public ThermalZone {
protected:
    int _getLoad() override;
    int _getTemp() override;

private:
    void readSmi();

};


#endif //CFAN_THERMALNVIDIAGPU_H
