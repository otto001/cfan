//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_THERMALZONE_H
#define CFAN_THERMALZONE_H

#include <string>
#include <filesystem>
#include <yaml-cpp/yaml.h>


class ThermalZone {
public:

    ThermalZone() = default;
    virtual ~ThermalZone() = default;

    friend class Detector;

protected:
    std::string name;
#if WIN32
#else
    std::filesystem::path path;
    [[nodiscard]] const std::filesystem::path &getPath() const {
        return path;
    }

#endif
public:
    [[nodiscard]] const std::string &getName() const;

protected:
    int idle = 50;
    int desired = 60;
    int critical = 80;

    int tempCache = -1;
    int loadCache = -1;

    virtual int _getTemp();
    virtual int _getLoad();
    virtual bool load(YAML::Node node);

public:
    virtual YAML::Node* writeToYamlNode();

    virtual void update();

    virtual int getTemp() final;
    virtual int getLoad() final;
    [[nodiscard]] virtual double getScore() final;

    static ThermalZone* loadZone(YAML::Node& node);

};


#endif //CFAN_THERMALZONE_H
