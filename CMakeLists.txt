cmake_minimum_required(VERSION 3.17)
project(cfan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(libs/yaml-cpp)


include_directories(libs/yaml-cpp/include)
add_executable(cfan main.cpp Control.cpp Control.h cooling/CoolingDevice.cpp cooling/CoolingDevice.h thermal/ThermalZone.cpp thermal/ThermalZone.h thermal/ThermalCpu.cpp thermal/ThermalCpu.h utils.h utils.cpp thermal/ThermalNvidiaGpu.cpp thermal/ThermalNvidiaGpu.h detection/Detector.cpp detection/Detector.h system-utils.cpp system-utils.h)

target_link_libraries(cfan yaml-cpp)

#find_package(Curses REQUIRED)

#target_link_libraries(cfan ${CURSES_LIBRARIES})

# maybe needed in unix?
# target_link_libraries(cfan stdc++fs)


#install(TARGETS cfan DESTINATION /usr/local/bin/)
#install(FILES cfan.service DESTINATION /etc/systemd/system/)
#install(CODE "execute_process(COMMAND /bin/sh enable-service.sh
#            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})")

