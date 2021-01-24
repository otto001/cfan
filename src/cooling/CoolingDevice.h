//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_COOLINGDEVICE_H
#define CFAN_COOLINGDEVICE_H

#include <string>
#include <filesystem>
#include "../thermal/ThermalZone.h"

class Control;

class CoolingDevice {
public:
    CoolingDevice(Control *control);

    friend class Detector;

protected:
    Control *control;
#if WIN32
#else
protected:
    std::filesystem::path path;
public:
    [[nodiscard]] inline const std::filesystem::path &getPath() const {
        return path;
    }

    inline void setPath(const std::filesystem::path &_path) {
        CoolingDevice::path = _path;
    }

    [[nodiscard]] inline std::filesystem::path getHwmonPath() const {
        return path.parent_path();
    }

    [[nodiscard]] inline std::filesystem::path getPwmPath() const {
        return getPath();
    }

    [[nodiscard]] inline std::filesystem::path getFanPath() const {
        return getHwmonPath().append("fan" + std::to_string(getIndex()));
    }

#endif

protected:
    std::string name;
    uint8_t index;
public:
    inline void setName(const std::string &_name) { this->name = _name; };

    [[nodiscard]] inline bool getIsPump() const { return isPump; };

    inline void setIsPump(bool _isPump) { isPump = _isPump; };

    [[nodiscard]] inline const int *getRpmCurve() const { return rpmCurve; };

    [[nodiscard]] inline double getStartSpeed() const { return startSpeed; };

    inline void setStartSpeed(double _startSpeed) { startSpeed = _startSpeed; };

    [[nodiscard]] inline double getMinSpeed() const { return minSpeed; };

    inline void setMinSpeed(double _minSpeed) { minSpeed = _minSpeed; };

protected:

    bool isPump = false;
    int rpmCurve[11]{};
    double startSpeed = 0.0;
    double minSpeed = 0.0;
    double maxSpeed = 1.0;
    double lazinessStart = 0.6;
    double lazinessStop = 0.6;
    double linearity = 0.0;

    std::vector<ThermalZone *> thermalZones;
public:


    [[nodiscard]] const std::string &getName() const { return name; };
    [[nodiscard]] uint8_t getIndex() const { return index; };

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

    double buildUp = 0;
    static constexpr double buildUpThreshold = 1000;
    short unresponsiveCounter = 0;

    bool setSpeed(double speed, bool force = false);

    bool setToManual();

    bool setToSmartFanIVFanControl();

    [[nodiscard]] int readRpm() const;


    [[nodiscard]] ThermalZone *getHottestZone();

    virtual bool load(YAML::Node node);

    virtual YAML::Node *writeToYamlNode();


    virtual double getSpeedFromCurve(double x);

    virtual bool checkIsResponsive();

    virtual double calculateActualPwmSpeed();

public:

    virtual bool init();

    virtual void update();

    static CoolingDevice *loadDevice(YAML::Node &node, Control *control);


};


#endif //CFAN_COOLINGDEVICE_H
