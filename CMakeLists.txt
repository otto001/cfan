cmake_minimum_required(VERSION 3.17)
project(cfan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cfan main.cpp Control.cpp Control.h CoolingDevice.cpp CoolingDevice.h thermal/ThermalZone.cpp thermal/ThermalZone.h thermal/ThermalCpu.cpp thermal/ThermalCpu.h utils.h utils.cpp thermal/ThermalNvidiaGpu.cpp thermal/ThermalNvidiaGpu.h Table.h Table.cpp detection/Detector.cpp detection/Detector.h system-utils.cpp system-utils.h)


include_directories(libs/yaml-cpp/include)
add_subdirectory(libs/yaml-cpp)
target_link_libraries(cfan libyaml-cpp)

#find_package(Curses REQUIRED)

#target_link_libraries(cfan ${CURSES_LIBRARIES})
target_link_libraries(cfan stdc++fs)