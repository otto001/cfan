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

    std::vector<std::string> tempPaths;

    bool load(YAML::Node node) override;

public:

};


#endif //CFAN_THERMALCPU_H
