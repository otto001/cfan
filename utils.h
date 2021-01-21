//
// Created by otto001 on 9/7/20.
//

#ifndef CFAN_UTILS_H
#define CFAN_UTILS_H

#include <string>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <exception>
#include <utility>
#include <iostream>

#define SEC_TO_MICROSEC(x) ((x)*1000000)

std::string readFile(const std::string& path);
int parseInt(const std::string& value);
int readIntFromFile(const std::string& path);

std::string exec(const char* cmd);

// trim from start (in place)
inline void ltrim(std::string &s);
// trim from end (in place)
inline void rtrim(std::string &s);
// trim from both ends (in place)
inline void trim(std::string &s);


inline double lerp(double a, double b, double alpha) {
    return a*(1-alpha) + b*alpha;
}

bool isYes(const std::string string);


class LoadingException : public std::exception {
    std::string location;
    std::string msg;

public:
    explicit LoadingException(const std::string& location);

    [[nodiscard]] const std::string& getLocation() const { return location; }
    [[nodiscard]] const char* what() const noexcept(true) override;

};


template<typename T>
T readYamlField(YAML::Node node, const std::string& name) {
    try {
        return node[name].as<T>();
    } catch (YAML::BadConversion& e) {
        throw LoadingException(name);
    }
}


template<typename T>
T readYamlField(YAML::Node node, const std::string& name, T defaultValue) {
    try {
        return node[name].as<T>();
    } catch (YAML::BadConversion& e) {
        return defaultValue;
    }
}

char asciiToLower(char in);

#endif //CFAN_UTILS_H
