//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_THERMALGPU_H
#define CFAN_THERMALGPU_H

#include <vector>
#include <string>

#include "ThermalZone.h"


class ThermalGpu : public ThermalZone {
public:
    ThermalGpu() = default;
    virtual ~ThermalGpu() = default;
protected:
    int _getLoad() override;
    int _getTemp() override;
    bool load(YAML::Node node) override;

};


#endif //CFAN_THERMALGPU_H
