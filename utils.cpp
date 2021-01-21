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
#include <cctype>

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

bool isYes(const std::string string) {
    std::string lowercase = string;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(),
                   [](unsigned char c){ return asciiToLower(c); });
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
