# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug"

# Utility rule file for BlutoothCmd-size.

# Include the progress variables for this target.
include CMakeFiles/BlutoothCmd-size.dir/progress.make

CMakeFiles/BlutoothCmd-size: BlutoothCmd.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Calculating BlutoothCmd image size"
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -DFIRMWARE_IMAGE=/Users/eg_julien/Google\ Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug/BlutoothCmd.elf -DMCU=atmega328p -DEEPROM_IMAGE=/Users/eg_julien/Google\ Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug/BlutoothCmd.eep -P /Users/eg_julien/Google\ Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

BlutoothCmd-size: CMakeFiles/BlutoothCmd-size
BlutoothCmd-size: CMakeFiles/BlutoothCmd-size.dir/build.make

.PHONY : BlutoothCmd-size

# Rule to build all files generated by this target.
CMakeFiles/BlutoothCmd-size.dir/build: BlutoothCmd-size

.PHONY : CMakeFiles/BlutoothCmd-size.dir/build

CMakeFiles/BlutoothCmd-size.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BlutoothCmd-size.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BlutoothCmd-size.dir/clean

CMakeFiles/BlutoothCmd-size.dir/depend:
	cd "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd" "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd" "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug" "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug" "/Users/eg_julien/Google Drive/Projects/RobotPong/V2.0/RobotPongSoft/RbtPongSoft/BlutoothCmd/cmake-build-debug/CMakeFiles/BlutoothCmd-size.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/BlutoothCmd-size.dir/depend

