//
// Created by ludwig on 1/21/21.
//

#ifndef CFAN_DETECTOR_H
#define CFAN_DETECTOR_H

#include <vector>

class Control;
class CoolingDevice;

class Detector {
public:
    Detector(Control* control);
protected:
    Control* control;
public:
    void run();
    void detectThermal();
    void detectThermalHwmon(std::filesystem::path path);

    void detectCooling();
    std::vector<CoolingDevice *> getCoolingDevicesFromHwmon(std::filesystem::path path);
    void resetCoolingDevicesSpeed(const std::vector<CoolingDevice *> &devices, const double speed);
};


#endif //CFAN_DETECTOR_H
