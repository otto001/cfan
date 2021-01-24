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
        devices/SmBios.cpp superIo/SmBios.h devices/MainBoard.cpp devices/MainBoard.h devices/Device.cpp devices/Device.h
        superIo/NCT6775.cpp superIo/NCT6775.h superIo/SuperIo.cpp superIo/SuperIo.h


        )
target_link_libraries(winfan WinRing0x64)
