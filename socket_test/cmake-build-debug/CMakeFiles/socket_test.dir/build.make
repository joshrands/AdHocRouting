# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/socket_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/socket_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socket_test.dir/flags.make

CMakeFiles/socket_test.dir/Endpoint.cpp.o: CMakeFiles/socket_test.dir/flags.make
CMakeFiles/socket_test.dir/Endpoint.cpp.o: ../Endpoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/socket_test.dir/Endpoint.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socket_test.dir/Endpoint.cpp.o -c /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Endpoint.cpp

CMakeFiles/socket_test.dir/Endpoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket_test.dir/Endpoint.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Endpoint.cpp > CMakeFiles/socket_test.dir/Endpoint.cpp.i

CMakeFiles/socket_test.dir/Endpoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket_test.dir/Endpoint.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Endpoint.cpp -o CMakeFiles/socket_test.dir/Endpoint.cpp.s

CMakeFiles/socket_test.dir/Pi2.cpp.o: CMakeFiles/socket_test.dir/flags.make
CMakeFiles/socket_test.dir/Pi2.cpp.o: ../Pi2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/socket_test.dir/Pi2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socket_test.dir/Pi2.cpp.o -c /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Pi2.cpp

CMakeFiles/socket_test.dir/Pi2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket_test.dir/Pi2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Pi2.cpp > CMakeFiles/socket_test.dir/Pi2.cpp.i

CMakeFiles/socket_test.dir/Pi2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket_test.dir/Pi2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Pi2.cpp -o CMakeFiles/socket_test.dir/Pi2.cpp.s

CMakeFiles/socket_test.dir/Socket.cpp.o: CMakeFiles/socket_test.dir/flags.make
CMakeFiles/socket_test.dir/Socket.cpp.o: ../Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/socket_test.dir/Socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socket_test.dir/Socket.cpp.o -c /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Socket.cpp

CMakeFiles/socket_test.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket_test.dir/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Socket.cpp > CMakeFiles/socket_test.dir/Socket.cpp.i

CMakeFiles/socket_test.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket_test.dir/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/Socket.cpp -o CMakeFiles/socket_test.dir/Socket.cpp.s

CMakeFiles/socket_test.dir/UDPSocket.cpp.o: CMakeFiles/socket_test.dir/flags.make
CMakeFiles/socket_test.dir/UDPSocket.cpp.o: ../UDPSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/socket_test.dir/UDPSocket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/socket_test.dir/UDPSocket.cpp.o -c /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/UDPSocket.cpp

CMakeFiles/socket_test.dir/UDPSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socket_test.dir/UDPSocket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/UDPSocket.cpp > CMakeFiles/socket_test.dir/UDPSocket.cpp.i

CMakeFiles/socket_test.dir/UDPSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socket_test.dir/UDPSocket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/UDPSocket.cpp -o CMakeFiles/socket_test.dir/UDPSocket.cpp.s

# Object files for target socket_test
socket_test_OBJECTS = \
"CMakeFiles/socket_test.dir/Endpoint.cpp.o" \
"CMakeFiles/socket_test.dir/Pi2.cpp.o" \
"CMakeFiles/socket_test.dir/Socket.cpp.o" \
"CMakeFiles/socket_test.dir/UDPSocket.cpp.o"

# External object files for target socket_test
socket_test_EXTERNAL_OBJECTS =

socket_test: CMakeFiles/socket_test.dir/Endpoint.cpp.o
socket_test: CMakeFiles/socket_test.dir/Pi2.cpp.o
socket_test: CMakeFiles/socket_test.dir/Socket.cpp.o
socket_test: CMakeFiles/socket_test.dir/UDPSocket.cpp.o
socket_test: CMakeFiles/socket_test.dir/build.make
socket_test: CMakeFiles/socket_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable socket_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socket_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socket_test.dir/build: socket_test

.PHONY : CMakeFiles/socket_test.dir/build

CMakeFiles/socket_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/socket_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/socket_test.dir/clean

CMakeFiles/socket_test.dir/depend:
	cd /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug /home/zsmeton/Dropbox/Research/SmallSat/AdHocRouting/socket_test/cmake-build-debug/CMakeFiles/socket_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/socket_test.dir/depend

