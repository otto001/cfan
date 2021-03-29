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
    bool load(YAML::Node node) override;

public:
    YAML::Node* writeToYamlNode() override;
};
;


#endif //CFAN_THERMALPROBE_H
