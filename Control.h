//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_CONTROL_H
#define CFAN_CONTROL_H

#include <vector>
#include "thermal/ThermalZone.h"
#include "cooling/CoolingDevice.h"

class Control {
public:
    friend class Detector;

    [[nodiscard]] const std::vector<ThermalZone *> &getThermalZones() const;

    [[nodiscard]] const std::vector<CoolingDevice *> &getCoolingDevices() const;

    static constexpr char configPath [] = "/etc/cfan/config.yml";
    static constexpr char sysPath [] = "/sys/cfan";

private:
    std::vector<ThermalZone*> thermalZones;
    std::vector<CoolingDevice*> coolingDevices;


    void update();
    void writeToStdout();
    int interval = 500;
public:
    [[nodiscard]] int getInterval() const;
    //ms


public:
    bool load();
    bool save();

    void init();
    [[noreturn]] void run();
    [[noreturn]] void curses();
    void detect();

    ThermalZone* getThermalZone(const std::string& name);

    bool debug = false;

};


#endif //CFAN_CONTROL_H
