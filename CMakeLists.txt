cmake_minimum_required(VERSION 3.17)
project(cfan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(libs/yaml-cpp)
include_directories(libs/yaml-cpp/include)

IF (WIN32)
    add_subdirectory(libs/winfan)
    include_directories(libs/winfan/include)
ENDIF()


add_executable(cfan src/main.cpp src/Control.cpp src/Control.h src/cooling/CoolingDevice.cpp src/cooling/CoolingDevice.h src/thermal/ThermalZone.cpp src/thermal/ThermalZone.h src/thermal/ThermalCpu.cpp src/thermal/ThermalCpu.h src/utils.h src/utils.cpp src/thermal/ThermalNvidiaGpu.cpp src/thermal/ThermalNvidiaGpu.h src/detection/Detector.cpp src/detection/Detector.h src/system-utils.cpp src/system-utils.h libs/winfan/include/winfan/winfan.h)


target_link_libraries(cfan yaml-cpp)
IF (WIN32)
    target_link_libraries(cfan winfan)
ENDIF()

#find_package(Curses REQUIRED)

#target_link_libraries(cfan ${CURSES_LIBRARIES})

# maybe needed in unix?
# target_link_libraries(cfan stdc++fs)


#install(TARGETS cfan DESTINATION /usr/local/bin/)
#install(FILES cfan.service DESTINATION /etc/systemd/system/)
#install(CODE "execute_process(COMMAND /bin/sh enable-service.sh
#            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})")

