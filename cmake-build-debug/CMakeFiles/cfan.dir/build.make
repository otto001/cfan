# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/clion-2020.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/clion-2020.2.1/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/otto001/projects/cfan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/otto001/projects/cfan/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cfan.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cfan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cfan.dir/flags.make

CMakeFiles/cfan.dir/main.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cfan.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/main.cpp.o -c /home/otto001/projects/cfan/main.cpp

CMakeFiles/cfan.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/main.cpp > CMakeFiles/cfan.dir/main.cpp.i

CMakeFiles/cfan.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/main.cpp -o CMakeFiles/cfan.dir/main.cpp.s

CMakeFiles/cfan.dir/Control.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/Control.cpp.o: ../Control.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cfan.dir/Control.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/Control.cpp.o -c /home/otto001/projects/cfan/Control.cpp

CMakeFiles/cfan.dir/Control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/Control.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/Control.cpp > CMakeFiles/cfan.dir/Control.cpp.i

CMakeFiles/cfan.dir/Control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/Control.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/Control.cpp -o CMakeFiles/cfan.dir/Control.cpp.s

CMakeFiles/cfan.dir/CoolingDevice.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/CoolingDevice.cpp.o: ../CoolingDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cfan.dir/CoolingDevice.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/CoolingDevice.cpp.o -c /home/otto001/projects/cfan/CoolingDevice.cpp

CMakeFiles/cfan.dir/CoolingDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/CoolingDevice.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/CoolingDevice.cpp > CMakeFiles/cfan.dir/CoolingDevice.cpp.i

CMakeFiles/cfan.dir/CoolingDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/CoolingDevice.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/CoolingDevice.cpp -o CMakeFiles/cfan.dir/CoolingDevice.cpp.s

CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o: ../thermal/ThermalZone.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o -c /home/otto001/projects/cfan/thermal/ThermalZone.cpp

CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/thermal/ThermalZone.cpp > CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.i

CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/thermal/ThermalZone.cpp -o CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.s

CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o: ../thermal/ThermalCpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o -c /home/otto001/projects/cfan/thermal/ThermalCpu.cpp

CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/thermal/ThermalCpu.cpp > CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.i

CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/thermal/ThermalCpu.cpp -o CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.s

CMakeFiles/cfan.dir/utils.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/utils.cpp.o: ../utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cfan.dir/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/utils.cpp.o -c /home/otto001/projects/cfan/utils.cpp

CMakeFiles/cfan.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/utils.cpp > CMakeFiles/cfan.dir/utils.cpp.i

CMakeFiles/cfan.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/utils.cpp -o CMakeFiles/cfan.dir/utils.cpp.s

CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o: ../thermal/ThermalNvidiaGpu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o -c /home/otto001/projects/cfan/thermal/ThermalNvidiaGpu.cpp

CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/thermal/ThermalNvidiaGpu.cpp > CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.i

CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/thermal/ThermalNvidiaGpu.cpp -o CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.s

CMakeFiles/cfan.dir/Table.cpp.o: CMakeFiles/cfan.dir/flags.make
CMakeFiles/cfan.dir/Table.cpp.o: ../Table.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/cfan.dir/Table.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cfan.dir/Table.cpp.o -c /home/otto001/projects/cfan/Table.cpp

CMakeFiles/cfan.dir/Table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cfan.dir/Table.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/otto001/projects/cfan/Table.cpp > CMakeFiles/cfan.dir/Table.cpp.i

CMakeFiles/cfan.dir/Table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cfan.dir/Table.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/otto001/projects/cfan/Table.cpp -o CMakeFiles/cfan.dir/Table.cpp.s

# Object files for target cfan
cfan_OBJECTS = \
"CMakeFiles/cfan.dir/main.cpp.o" \
"CMakeFiles/cfan.dir/Control.cpp.o" \
"CMakeFiles/cfan.dir/CoolingDevice.cpp.o" \
"CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o" \
"CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o" \
"CMakeFiles/cfan.dir/utils.cpp.o" \
"CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o" \
"CMakeFiles/cfan.dir/Table.cpp.o"

# External object files for target cfan
cfan_EXTERNAL_OBJECTS =

cfan: CMakeFiles/cfan.dir/main.cpp.o
cfan: CMakeFiles/cfan.dir/Control.cpp.o
cfan: CMakeFiles/cfan.dir/CoolingDevice.cpp.o
cfan: CMakeFiles/cfan.dir/thermal/ThermalZone.cpp.o
cfan: CMakeFiles/cfan.dir/thermal/ThermalCpu.cpp.o
cfan: CMakeFiles/cfan.dir/utils.cpp.o
cfan: CMakeFiles/cfan.dir/thermal/ThermalNvidiaGpu.cpp.o
cfan: CMakeFiles/cfan.dir/Table.cpp.o
cfan: CMakeFiles/cfan.dir/build.make
cfan: /usr/lib/x86_64-linux-gnu/libcurses.so
cfan: /usr/lib/x86_64-linux-gnu/libform.so
cfan: CMakeFiles/cfan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/otto001/projects/cfan/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable cfan"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cfan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cfan.dir/build: cfan

.PHONY : CMakeFiles/cfan.dir/build

CMakeFiles/cfan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cfan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cfan.dir/clean

CMakeFiles/cfan.dir/depend:
	cd /home/otto001/projects/cfan/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/otto001/projects/cfan /home/otto001/projects/cfan /home/otto001/projects/cfan/cmake-build-debug /home/otto001/projects/cfan/cmake-build-debug /home/otto001/projects/cfan/cmake-build-debug/CMakeFiles/cfan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cfan.dir/depend

