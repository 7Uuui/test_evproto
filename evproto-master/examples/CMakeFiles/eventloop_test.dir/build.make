# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/local/evproto-master/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/evproto-master/examples

# Include any dependencies generated for this target.
include CMakeFiles/eventloop_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eventloop_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eventloop_test.dir/flags.make

CMakeFiles/eventloop_test.dir/eventloop_test.o: CMakeFiles/eventloop_test.dir/flags.make
CMakeFiles/eventloop_test.dir/eventloop_test.o: eventloop_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/examples/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/eventloop_test.dir/eventloop_test.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/eventloop_test.dir/eventloop_test.o -c /usr/local/evproto-master/examples/eventloop_test.cc

CMakeFiles/eventloop_test.dir/eventloop_test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eventloop_test.dir/eventloop_test.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/examples/eventloop_test.cc > CMakeFiles/eventloop_test.dir/eventloop_test.i

CMakeFiles/eventloop_test.dir/eventloop_test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eventloop_test.dir/eventloop_test.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/examples/eventloop_test.cc -o CMakeFiles/eventloop_test.dir/eventloop_test.s

CMakeFiles/eventloop_test.dir/eventloop_test.o.requires:
.PHONY : CMakeFiles/eventloop_test.dir/eventloop_test.o.requires

CMakeFiles/eventloop_test.dir/eventloop_test.o.provides: CMakeFiles/eventloop_test.dir/eventloop_test.o.requires
	$(MAKE) -f CMakeFiles/eventloop_test.dir/build.make CMakeFiles/eventloop_test.dir/eventloop_test.o.provides.build
.PHONY : CMakeFiles/eventloop_test.dir/eventloop_test.o.provides

CMakeFiles/eventloop_test.dir/eventloop_test.o.provides.build: CMakeFiles/eventloop_test.dir/eventloop_test.o

# Object files for target eventloop_test
eventloop_test_OBJECTS = \
"CMakeFiles/eventloop_test.dir/eventloop_test.o"

# External object files for target eventloop_test
eventloop_test_EXTERNAL_OBJECTS =

eventloop_test: CMakeFiles/eventloop_test.dir/eventloop_test.o
eventloop_test: CMakeFiles/eventloop_test.dir/build.make
eventloop_test: CMakeFiles/eventloop_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable eventloop_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eventloop_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eventloop_test.dir/build: eventloop_test
.PHONY : CMakeFiles/eventloop_test.dir/build

CMakeFiles/eventloop_test.dir/requires: CMakeFiles/eventloop_test.dir/eventloop_test.o.requires
.PHONY : CMakeFiles/eventloop_test.dir/requires

CMakeFiles/eventloop_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eventloop_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eventloop_test.dir/clean

CMakeFiles/eventloop_test.dir/depend:
	cd /usr/local/evproto-master/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/evproto-master/examples /usr/local/evproto-master/examples /usr/local/evproto-master/examples /usr/local/evproto-master/examples /usr/local/evproto-master/examples/CMakeFiles/eventloop_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eventloop_test.dir/depend

