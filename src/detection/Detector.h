//
// Created by ludwig on 1/21/21.
//

#ifndef CFAN_DETECTOR_H
#define CFAN_DETECTOR_H

#include <vector>

class Control;
class CoolingDevice;
class ThermalZone;

class Detector {
public:
    Detector(Control* control);
protected:
    Control* control;
public:
    void run();
    void detectThermal();
    std::vector<ThermalZone *> getThermalZonesFromHwmon(const std::filesystem::path& hwmonPath);

    void detectCooling();
    std::vector<CoolingDevice *> getCoolingDevicesFromHwmon(const std::filesystem::path& path);
    static void resetCoolingDevicesSpeed(const std::vector<CoolingDevice *> &devices, const double speed);
    static bool stopDevice(CoolingDevice* device);
    static bool waitForDeviceToStabilize(CoolingDevice *device, int timeout=40);
};


#endif //CFAN_DETECTOR_H
