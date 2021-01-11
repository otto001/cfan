//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_COOLINGDEVICE_H
#define CFAN_COOLINGDEVICE_H

#include <string>
#include <filesystem>
#include "thermal/ThermalZone.h"

class Control;

class CoolingDevice {
public:
    CoolingDevice(Control* control);
protected:
    Control* control;
    std::filesystem::path path;

    std::string name;

    bool isPump = false;
    int rpmCurve[11]{};
    double startSpeed = 0.0;
    double minSpeed = 0.0;
    double lazinessStart = 0.6;
    double lazinessStop = 0.6;
    double linearity = 0.0;

    std::vector<ThermalZone*> thermalZones;
public:


    [[nodiscard]] const std::filesystem::path &getPath() const;

    [[nodiscard]] const std::string &getName() const;

protected:
    // runtime
    double currentSetSpeed = 0;
    int currentSetSpeedInt = -1;
    double currentHighScore = 0;

public:
    [[nodiscard]] double getCurrentHighScore() const;
    [[nodiscard]] bool getIsStarted() const;
    [[nodiscard]] double getCurrentSetSpeed() const;
    [[nodiscard]] double getBuildUp() const;

protected:

    double buildUp = 0;
    static constexpr double buildUpThreshold = 1000;
    short unresponsiveCounter = 0;

    bool setSpeed(double speed, bool force=false);

    bool setToManual();

    [[nodiscard]] int readRpm();


    [[nodiscard]] std::filesystem::path getHwmonPath() const;

    [[nodiscard]] std::filesystem::path getPwmPath() const;

    [[nodiscard]] std::filesystem::path getFanPath() const;

    [[nodiscard]] int getIndex() const;

    [[nodiscard]] ThermalZone *getHottestZone();


    virtual bool load(YAML::Node node);

    virtual double getSpeedFromCurve(double x);
    virtual bool checkIsResponsive();
    virtual double calculateActualPwmSpeed();

public:

    virtual bool init();
    virtual void update();

    static CoolingDevice* loadDevice(YAML::Node& node, Control* control);


};


#endif //CFAN_COOLINGDEVICE_H
