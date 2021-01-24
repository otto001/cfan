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


// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from both ends (in place)
inline void toLower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}

inline double lerp(double a, double b, double alpha) {
    return a*(1-alpha) + b*alpha;
}

bool isYes(const std::string string);

template<typename T>
std::string join(const T arr[], size_t n, std::string sep) {
    std::string result;

    for (int i = 0; i < n; ++i) {
        result += std::to_string(arr[i]);
        if (i < n-1) {
            result += sep;
        }
    }
    return result;
}

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
