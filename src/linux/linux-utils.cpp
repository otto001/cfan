//
// Created by root on 1/25/21.
//

#include <filesystem>
#include "linux-utils.h"
#include "../utils.h"

bool getHwmonPathByName(std::filesystem::path &path, const std::string &name)  {
    std::string baseDir = "/sys/class/hwmon";

    for (const auto &entry : std::filesystem::directory_iterator(baseDir)) {
        if (entry.is_directory()) {
            auto hwmonName = readFile((entry.path() / "name").string());
            rtrim(hwmonName);
            if (hwmonName == name) {
                path = entry.path();
                return true;
            }
        }
    }
    return false;
}
