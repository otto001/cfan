//
// Created by root on 3/29/21.
//

#ifndef CFAN_THERMALPROBE_H
#define CFAN_THERMALPROBE_H

#include "ThermalZone.h"


class ThermalProbe : public ThermalZone {
public:

    ThermalProbe() = default;
    ~ThermalProbe() override = default;

    friend class Detector;


protected:
    bool load(YAML::Node& node) override;
    int _getTemp() override;

#if WIN32
    int32_t index;
#endif

public:
    YAML::Node* writeToYamlNode() override;
};
;


#endif //CFAN_THERMALPROBE_H
