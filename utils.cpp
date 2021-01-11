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

int parseInt(const std::string& value) {
    try {
        return (int) std::stoi(value);
    } catch (std::invalid_argument &e) {
        return -1;
    } catch (std::out_of_range &e) {
        return -1;
    }
}

int readIntFromPath(const std::string& path) {

    std::ifstream file;
    file.open(path);

    if (file.is_open()) {
        std::string value;
        getline(file, value);
        return parseInt(value);
    }

    return -1;
}


std::string exec(const char* cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


const char *LoadingException::what() const noexcept(true) {
    return msg.c_str();
}

LoadingException::LoadingException(const std::string& location) : location(location) {
    msg = ("FATAL: Error reading " + location + " from cfan config.yaml");
}
