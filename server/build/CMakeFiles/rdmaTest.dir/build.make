# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hjkim/Lets_go_RDMA/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hjkim/Lets_go_RDMA/server/build

# Include any dependencies generated for this target.
include CMakeFiles/rdmaTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rdmaTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rdmaTest.dir/flags.make

CMakeFiles/rdmaTest.dir/main.cpp.o: CMakeFiles/rdmaTest.dir/flags.make
CMakeFiles/rdmaTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hjkim/Lets_go_RDMA/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rdmaTest.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rdmaTest.dir/main.cpp.o -c /home/hjkim/Lets_go_RDMA/server/main.cpp

CMakeFiles/rdmaTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rdmaTest.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hjkim/Lets_go_RDMA/server/main.cpp > CMakeFiles/rdmaTest.dir/main.cpp.i

CMakeFiles/rdmaTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rdmaTest.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hjkim/Lets_go_RDMA/server/main.cpp -o CMakeFiles/rdmaTest.dir/main.cpp.s

# Object files for target rdmaTest
rdmaTest_OBJECTS = \
"CMakeFiles/rdmaTest.dir/main.cpp.o"

# External object files for target rdmaTest
rdmaTest_EXTERNAL_OBJECTS =

rdmaTest: CMakeFiles/rdmaTest.dir/main.cpp.o
rdmaTest: CMakeFiles/rdmaTest.dir/build.make
rdmaTest: src/tools/libtools.a
rdmaTest: src/network/libnetwork.a
rdmaTest: CMakeFiles/rdmaTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hjkim/Lets_go_RDMA/server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rdmaTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rdmaTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rdmaTest.dir/build: rdmaTest

.PHONY : CMakeFiles/rdmaTest.dir/build

CMakeFiles/rdmaTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rdmaTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rdmaTest.dir/clean

CMakeFiles/rdmaTest.dir/depend:
	cd /home/hjkim/Lets_go_RDMA/server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hjkim/Lets_go_RDMA/server /home/hjkim/Lets_go_RDMA/server /home/hjkim/Lets_go_RDMA/server/build /home/hjkim/Lets_go_RDMA/server/build /home/hjkim/Lets_go_RDMA/server/build/CMakeFiles/rdmaTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rdmaTest.dir/depend

