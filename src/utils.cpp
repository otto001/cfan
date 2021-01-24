//
// Created by otto001 on 9/7/20.
//
#include "utils.h"

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>

std::string readFile(const std::string &path) {
    std::ifstream file;
    file.open(path);

    if (file.is_open()) {
        std::string str((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
        return str;
    }

    return "";
}

int parseInt(const std::string& value) {
    try {
        return (int) std::stoi(value);
    } catch (std::invalid_argument &e) {
        return -1;
    } catch (std::out_of_range &e) {
        return -1;
    }
}

int readIntFromFile(const std::string& path) {
    return parseInt(readFile(path));
}




bool isYes(const std::string string) {
    std::string lowercase = string;
    toLower(lowercase);
    return lowercase == "yes" || lowercase == "y" || lowercase == "1" || lowercase == "t" || lowercase == "true";
}

char asciiToLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

const char *LoadingException::what() const noexcept(true) {
    return msg.c_str();
}



LoadingException::LoadingException(const std::string& location) : location(location) {
    msg = ("FATAL: Error reading " + location + " from cfan config.yaml");
}
