cmake_minimum_required(VERSION 3.17)
project(winfan)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(_UNICODE)
add_compile_definitions(UNICODE)

add_subdirectory(libs/ols-api)
include_directories(libs/ols-api/include)

add_library(winfan main.cpp winfan.cpp
        OlsDll.h OlsDll.cpp
        lpcIo/LpcIo.cpp lpcIo/LpcIo.h lpcIo/LpcIoPort.cpp lpcIo/LpcIoPort.h
        devices/Devices.cpp devices/Devices.h devices/mainboard/MainBoard.cpp devices/mainboard/MainBoard.h devices/Device.cpp devices/Device.h
        devices/mainboard/superIo/NCT6775.cpp devices/mainboard/superIo/NCT6775.h devices/mainboard/superIo/SuperIo.cpp devices/mainboard/superIo/SuperIo.h


        devices/cpu/AMD19CPU.cpp devices/cpu/AMD19CPU.h devices/cpu/CPU.cpp devices/cpu/CPU.h)
target_link_libraries(winfan WinRing0x64)
