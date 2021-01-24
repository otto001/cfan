//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_THERMALCPU_H
#define CFAN_THERMALCPU_H

#include <vector>
#include <string>

#include "ThermalZone.h"


class ThermalCpu : public ThermalZone {
protected:
    int _getLoad() override;
    int _getTemp() override;

};


#endif //CFAN_THERMALCPU_H
