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
CMAKE_SOURCE_DIR = /usr/local/evproto-master/evproto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/evproto-master/evproto

# Include any dependencies generated for this target.
include CMakeFiles/evproto.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/evproto.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/evproto.dir/flags.make

CMakeFiles/evproto.dir/Acceptor.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Acceptor.o: Acceptor.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Acceptor.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Acceptor.o -c /usr/local/evproto-master/evproto/Acceptor.cc

CMakeFiles/evproto.dir/Acceptor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Acceptor.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Acceptor.cc > CMakeFiles/evproto.dir/Acceptor.i

CMakeFiles/evproto.dir/Acceptor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Acceptor.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Acceptor.cc -o CMakeFiles/evproto.dir/Acceptor.s

CMakeFiles/evproto.dir/Acceptor.o.requires:
.PHONY : CMakeFiles/evproto.dir/Acceptor.o.requires

CMakeFiles/evproto.dir/Acceptor.o.provides: CMakeFiles/evproto.dir/Acceptor.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Acceptor.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Acceptor.o.provides

CMakeFiles/evproto.dir/Acceptor.o.provides.build: CMakeFiles/evproto.dir/Acceptor.o

CMakeFiles/evproto.dir/Channel.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Channel.o: Channel.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Channel.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Channel.o -c /usr/local/evproto-master/evproto/Channel.cc

CMakeFiles/evproto.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Channel.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Channel.cc > CMakeFiles/evproto.dir/Channel.i

CMakeFiles/evproto.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Channel.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Channel.cc -o CMakeFiles/evproto.dir/Channel.s

CMakeFiles/evproto.dir/Channel.o.requires:
.PHONY : CMakeFiles/evproto.dir/Channel.o.requires

CMakeFiles/evproto.dir/Channel.o.provides: CMakeFiles/evproto.dir/Channel.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Channel.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Channel.o.provides

CMakeFiles/evproto.dir/Channel.o.provides.build: CMakeFiles/evproto.dir/Channel.o

CMakeFiles/evproto.dir/Poller.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Poller.o: Poller.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Poller.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Poller.o -c /usr/local/evproto-master/evproto/Poller.cc

CMakeFiles/evproto.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Poller.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Poller.cc > CMakeFiles/evproto.dir/Poller.i

CMakeFiles/evproto.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Poller.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Poller.cc -o CMakeFiles/evproto.dir/Poller.s

CMakeFiles/evproto.dir/Poller.o.requires:
.PHONY : CMakeFiles/evproto.dir/Poller.o.requires

CMakeFiles/evproto.dir/Poller.o.provides: CMakeFiles/evproto.dir/Poller.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Poller.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Poller.o.provides

CMakeFiles/evproto.dir/Poller.o.provides.build: CMakeFiles/evproto.dir/Poller.o

CMakeFiles/evproto.dir/EpollPoller.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/EpollPoller.o: EpollPoller.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/EpollPoller.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/EpollPoller.o -c /usr/local/evproto-master/evproto/EpollPoller.cc

CMakeFiles/evproto.dir/EpollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/EpollPoller.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/EpollPoller.cc > CMakeFiles/evproto.dir/EpollPoller.i

CMakeFiles/evproto.dir/EpollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/EpollPoller.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/EpollPoller.cc -o CMakeFiles/evproto.dir/EpollPoller.s

CMakeFiles/evproto.dir/EpollPoller.o.requires:
.PHONY : CMakeFiles/evproto.dir/EpollPoller.o.requires

CMakeFiles/evproto.dir/EpollPoller.o.provides: CMakeFiles/evproto.dir/EpollPoller.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/EpollPoller.o.provides.build
.PHONY : CMakeFiles/evproto.dir/EpollPoller.o.provides

CMakeFiles/evproto.dir/EpollPoller.o.provides.build: CMakeFiles/evproto.dir/EpollPoller.o

CMakeFiles/evproto.dir/eventloop.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/eventloop.o: eventloop.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/eventloop.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/eventloop.o -c /usr/local/evproto-master/evproto/eventloop.cc

CMakeFiles/evproto.dir/eventloop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/eventloop.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/eventloop.cc > CMakeFiles/evproto.dir/eventloop.i

CMakeFiles/evproto.dir/eventloop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/eventloop.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/eventloop.cc -o CMakeFiles/evproto.dir/eventloop.s

CMakeFiles/evproto.dir/eventloop.o.requires:
.PHONY : CMakeFiles/evproto.dir/eventloop.o.requires

CMakeFiles/evproto.dir/eventloop.o.provides: CMakeFiles/evproto.dir/eventloop.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/eventloop.o.provides.build
.PHONY : CMakeFiles/evproto.dir/eventloop.o.provides

CMakeFiles/evproto.dir/eventloop.o.provides.build: CMakeFiles/evproto.dir/eventloop.o

CMakeFiles/evproto.dir/EventLoopThread.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/EventLoopThread.o: EventLoopThread.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/EventLoopThread.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/EventLoopThread.o -c /usr/local/evproto-master/evproto/EventLoopThread.cc

CMakeFiles/evproto.dir/EventLoopThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/EventLoopThread.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/EventLoopThread.cc > CMakeFiles/evproto.dir/EventLoopThread.i

CMakeFiles/evproto.dir/EventLoopThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/EventLoopThread.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/EventLoopThread.cc -o CMakeFiles/evproto.dir/EventLoopThread.s

CMakeFiles/evproto.dir/EventLoopThread.o.requires:
.PHONY : CMakeFiles/evproto.dir/EventLoopThread.o.requires

CMakeFiles/evproto.dir/EventLoopThread.o.provides: CMakeFiles/evproto.dir/EventLoopThread.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/EventLoopThread.o.provides.build
.PHONY : CMakeFiles/evproto.dir/EventLoopThread.o.provides

CMakeFiles/evproto.dir/EventLoopThread.o.provides.build: CMakeFiles/evproto.dir/EventLoopThread.o

CMakeFiles/evproto.dir/EventLoopThreadPool.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/EventLoopThreadPool.o: EventLoopThreadPool.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/EventLoopThreadPool.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/EventLoopThreadPool.o -c /usr/local/evproto-master/evproto/EventLoopThreadPool.cc

CMakeFiles/evproto.dir/EventLoopThreadPool.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/EventLoopThreadPool.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/EventLoopThreadPool.cc > CMakeFiles/evproto.dir/EventLoopThreadPool.i

CMakeFiles/evproto.dir/EventLoopThreadPool.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/EventLoopThreadPool.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/EventLoopThreadPool.cc -o CMakeFiles/evproto.dir/EventLoopThreadPool.s

CMakeFiles/evproto.dir/EventLoopThreadPool.o.requires:
.PHONY : CMakeFiles/evproto.dir/EventLoopThreadPool.o.requires

CMakeFiles/evproto.dir/EventLoopThreadPool.o.provides: CMakeFiles/evproto.dir/EventLoopThreadPool.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/EventLoopThreadPool.o.provides.build
.PHONY : CMakeFiles/evproto.dir/EventLoopThreadPool.o.provides

CMakeFiles/evproto.dir/EventLoopThreadPool.o.provides.build: CMakeFiles/evproto.dir/EventLoopThreadPool.o

CMakeFiles/evproto.dir/evproto.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/evproto.o: evproto.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/evproto.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/evproto.o -c /usr/local/evproto-master/evproto/evproto.cc

CMakeFiles/evproto.dir/evproto.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/evproto.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/evproto.cc > CMakeFiles/evproto.dir/evproto.i

CMakeFiles/evproto.dir/evproto.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/evproto.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/evproto.cc -o CMakeFiles/evproto.dir/evproto.s

CMakeFiles/evproto.dir/evproto.o.requires:
.PHONY : CMakeFiles/evproto.dir/evproto.o.requires

CMakeFiles/evproto.dir/evproto.o.provides: CMakeFiles/evproto.dir/evproto.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/evproto.o.provides.build
.PHONY : CMakeFiles/evproto.dir/evproto.o.provides

CMakeFiles/evproto.dir/evproto.o.provides.build: CMakeFiles/evproto.dir/evproto.o

CMakeFiles/evproto.dir/rpcchannel.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/rpcchannel.o: rpcchannel.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/rpcchannel.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/rpcchannel.o -c /usr/local/evproto-master/evproto/rpcchannel.cc

CMakeFiles/evproto.dir/rpcchannel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/rpcchannel.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/rpcchannel.cc > CMakeFiles/evproto.dir/rpcchannel.i

CMakeFiles/evproto.dir/rpcchannel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/rpcchannel.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/rpcchannel.cc -o CMakeFiles/evproto.dir/rpcchannel.s

CMakeFiles/evproto.dir/rpcchannel.o.requires:
.PHONY : CMakeFiles/evproto.dir/rpcchannel.o.requires

CMakeFiles/evproto.dir/rpcchannel.o.provides: CMakeFiles/evproto.dir/rpcchannel.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/rpcchannel.o.provides.build
.PHONY : CMakeFiles/evproto.dir/rpcchannel.o.provides

CMakeFiles/evproto.dir/rpcchannel.o.provides.build: CMakeFiles/evproto.dir/rpcchannel.o

CMakeFiles/evproto.dir/rpccontroller.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/rpccontroller.o: rpccontroller.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/rpccontroller.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/rpccontroller.o -c /usr/local/evproto-master/evproto/rpccontroller.cc

CMakeFiles/evproto.dir/rpccontroller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/rpccontroller.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/rpccontroller.cc > CMakeFiles/evproto.dir/rpccontroller.i

CMakeFiles/evproto.dir/rpccontroller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/rpccontroller.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/rpccontroller.cc -o CMakeFiles/evproto.dir/rpccontroller.s

CMakeFiles/evproto.dir/rpccontroller.o.requires:
.PHONY : CMakeFiles/evproto.dir/rpccontroller.o.requires

CMakeFiles/evproto.dir/rpccontroller.o.provides: CMakeFiles/evproto.dir/rpccontroller.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/rpccontroller.o.provides.build
.PHONY : CMakeFiles/evproto.dir/rpccontroller.o.provides

CMakeFiles/evproto.dir/rpccontroller.o.provides.build: CMakeFiles/evproto.dir/rpccontroller.o

CMakeFiles/evproto.dir/rpcserver.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/rpcserver.o: rpcserver.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/rpcserver.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/rpcserver.o -c /usr/local/evproto-master/evproto/rpcserver.cc

CMakeFiles/evproto.dir/rpcserver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/rpcserver.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/rpcserver.cc > CMakeFiles/evproto.dir/rpcserver.i

CMakeFiles/evproto.dir/rpcserver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/rpcserver.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/rpcserver.cc -o CMakeFiles/evproto.dir/rpcserver.s

CMakeFiles/evproto.dir/rpcserver.o.requires:
.PHONY : CMakeFiles/evproto.dir/rpcserver.o.requires

CMakeFiles/evproto.dir/rpcserver.o.provides: CMakeFiles/evproto.dir/rpcserver.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/rpcserver.o.provides.build
.PHONY : CMakeFiles/evproto.dir/rpcserver.o.provides

CMakeFiles/evproto.dir/rpcserver.o.provides.build: CMakeFiles/evproto.dir/rpcserver.o

CMakeFiles/evproto.dir/Timestamp.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Timestamp.o: Timestamp.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Timestamp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Timestamp.o -c /usr/local/evproto-master/evproto/Timestamp.cc

CMakeFiles/evproto.dir/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Timestamp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Timestamp.cc > CMakeFiles/evproto.dir/Timestamp.i

CMakeFiles/evproto.dir/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Timestamp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Timestamp.cc -o CMakeFiles/evproto.dir/Timestamp.s

CMakeFiles/evproto.dir/Timestamp.o.requires:
.PHONY : CMakeFiles/evproto.dir/Timestamp.o.requires

CMakeFiles/evproto.dir/Timestamp.o.provides: CMakeFiles/evproto.dir/Timestamp.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Timestamp.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Timestamp.o.provides

CMakeFiles/evproto.dir/Timestamp.o.provides.build: CMakeFiles/evproto.dir/Timestamp.o

CMakeFiles/evproto.dir/Thread.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Thread.o: Thread.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Thread.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Thread.o -c /usr/local/evproto-master/evproto/Thread.cc

CMakeFiles/evproto.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Thread.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Thread.cc > CMakeFiles/evproto.dir/Thread.i

CMakeFiles/evproto.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Thread.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Thread.cc -o CMakeFiles/evproto.dir/Thread.s

CMakeFiles/evproto.dir/Thread.o.requires:
.PHONY : CMakeFiles/evproto.dir/Thread.o.requires

CMakeFiles/evproto.dir/Thread.o.provides: CMakeFiles/evproto.dir/Thread.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Thread.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Thread.o.provides

CMakeFiles/evproto.dir/Thread.o.provides.build: CMakeFiles/evproto.dir/Thread.o

CMakeFiles/evproto.dir/CurrentThread.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/CurrentThread.o: CurrentThread.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/CurrentThread.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/CurrentThread.o -c /usr/local/evproto-master/evproto/CurrentThread.cc

CMakeFiles/evproto.dir/CurrentThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/CurrentThread.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/CurrentThread.cc > CMakeFiles/evproto.dir/CurrentThread.i

CMakeFiles/evproto.dir/CurrentThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/CurrentThread.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/CurrentThread.cc -o CMakeFiles/evproto.dir/CurrentThread.s

CMakeFiles/evproto.dir/CurrentThread.o.requires:
.PHONY : CMakeFiles/evproto.dir/CurrentThread.o.requires

CMakeFiles/evproto.dir/CurrentThread.o.provides: CMakeFiles/evproto.dir/CurrentThread.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/CurrentThread.o.provides.build
.PHONY : CMakeFiles/evproto.dir/CurrentThread.o.provides

CMakeFiles/evproto.dir/CurrentThread.o.provides.build: CMakeFiles/evproto.dir/CurrentThread.o

CMakeFiles/evproto.dir/CountDownLatch.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/CountDownLatch.o: CountDownLatch.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/CountDownLatch.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/CountDownLatch.o -c /usr/local/evproto-master/evproto/CountDownLatch.cc

CMakeFiles/evproto.dir/CountDownLatch.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/CountDownLatch.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/CountDownLatch.cc > CMakeFiles/evproto.dir/CountDownLatch.i

CMakeFiles/evproto.dir/CountDownLatch.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/CountDownLatch.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/CountDownLatch.cc -o CMakeFiles/evproto.dir/CountDownLatch.s

CMakeFiles/evproto.dir/CountDownLatch.o.requires:
.PHONY : CMakeFiles/evproto.dir/CountDownLatch.o.requires

CMakeFiles/evproto.dir/CountDownLatch.o.provides: CMakeFiles/evproto.dir/CountDownLatch.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/CountDownLatch.o.provides.build
.PHONY : CMakeFiles/evproto.dir/CountDownLatch.o.provides

CMakeFiles/evproto.dir/CountDownLatch.o.provides.build: CMakeFiles/evproto.dir/CountDownLatch.o

CMakeFiles/evproto.dir/TcpConnection.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/TcpConnection.o: TcpConnection.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_16)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/TcpConnection.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/TcpConnection.o -c /usr/local/evproto-master/evproto/TcpConnection.cc

CMakeFiles/evproto.dir/TcpConnection.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/TcpConnection.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/TcpConnection.cc > CMakeFiles/evproto.dir/TcpConnection.i

CMakeFiles/evproto.dir/TcpConnection.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/TcpConnection.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/TcpConnection.cc -o CMakeFiles/evproto.dir/TcpConnection.s

CMakeFiles/evproto.dir/TcpConnection.o.requires:
.PHONY : CMakeFiles/evproto.dir/TcpConnection.o.requires

CMakeFiles/evproto.dir/TcpConnection.o.provides: CMakeFiles/evproto.dir/TcpConnection.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/TcpConnection.o.provides.build
.PHONY : CMakeFiles/evproto.dir/TcpConnection.o.provides

CMakeFiles/evproto.dir/TcpConnection.o.provides.build: CMakeFiles/evproto.dir/TcpConnection.o

CMakeFiles/evproto.dir/TcpClient.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/TcpClient.o: TcpClient.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_17)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/TcpClient.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/TcpClient.o -c /usr/local/evproto-master/evproto/TcpClient.cc

CMakeFiles/evproto.dir/TcpClient.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/TcpClient.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/TcpClient.cc > CMakeFiles/evproto.dir/TcpClient.i

CMakeFiles/evproto.dir/TcpClient.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/TcpClient.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/TcpClient.cc -o CMakeFiles/evproto.dir/TcpClient.s

CMakeFiles/evproto.dir/TcpClient.o.requires:
.PHONY : CMakeFiles/evproto.dir/TcpClient.o.requires

CMakeFiles/evproto.dir/TcpClient.o.provides: CMakeFiles/evproto.dir/TcpClient.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/TcpClient.o.provides.build
.PHONY : CMakeFiles/evproto.dir/TcpClient.o.provides

CMakeFiles/evproto.dir/TcpClient.o.provides.build: CMakeFiles/evproto.dir/TcpClient.o

CMakeFiles/evproto.dir/Connector.o: CMakeFiles/evproto.dir/flags.make
CMakeFiles/evproto.dir/Connector.o: Connector.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /usr/local/evproto-master/evproto/CMakeFiles $(CMAKE_PROGRESS_18)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/evproto.dir/Connector.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/evproto.dir/Connector.o -c /usr/local/evproto-master/evproto/Connector.cc

CMakeFiles/evproto.dir/Connector.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/evproto.dir/Connector.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /usr/local/evproto-master/evproto/Connector.cc > CMakeFiles/evproto.dir/Connector.i

CMakeFiles/evproto.dir/Connector.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/evproto.dir/Connector.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /usr/local/evproto-master/evproto/Connector.cc -o CMakeFiles/evproto.dir/Connector.s

CMakeFiles/evproto.dir/Connector.o.requires:
.PHONY : CMakeFiles/evproto.dir/Connector.o.requires

CMakeFiles/evproto.dir/Connector.o.provides: CMakeFiles/evproto.dir/Connector.o.requires
	$(MAKE) -f CMakeFiles/evproto.dir/build.make CMakeFiles/evproto.dir/Connector.o.provides.build
.PHONY : CMakeFiles/evproto.dir/Connector.o.provides

CMakeFiles/evproto.dir/Connector.o.provides.build: CMakeFiles/evproto.dir/Connector.o

# Object files for target evproto
evproto_OBJECTS = \
"CMakeFiles/evproto.dir/Acceptor.o" \
"CMakeFiles/evproto.dir/Channel.o" \
"CMakeFiles/evproto.dir/Poller.o" \
"CMakeFiles/evproto.dir/EpollPoller.o" \
"CMakeFiles/evproto.dir/eventloop.o" \
"CMakeFiles/evproto.dir/EventLoopThread.o" \
"CMakeFiles/evproto.dir/EventLoopThreadPool.o" \
"CMakeFiles/evproto.dir/evproto.o" \
"CMakeFiles/evproto.dir/rpcchannel.o" \
"CMakeFiles/evproto.dir/rpccontroller.o" \
"CMakeFiles/evproto.dir/rpcserver.o" \
"CMakeFiles/evproto.dir/Timestamp.o" \
"CMakeFiles/evproto.dir/Thread.o" \
"CMakeFiles/evproto.dir/CurrentThread.o" \
"CMakeFiles/evproto.dir/CountDownLatch.o" \
"CMakeFiles/evproto.dir/TcpConnection.o" \
"CMakeFiles/evproto.dir/TcpClient.o" \
"CMakeFiles/evproto.dir/Connector.o"

# External object files for target evproto
evproto_EXTERNAL_OBJECTS =

libevproto.a: CMakeFiles/evproto.dir/Acceptor.o
libevproto.a: CMakeFiles/evproto.dir/Channel.o
libevproto.a: CMakeFiles/evproto.dir/Poller.o
libevproto.a: CMakeFiles/evproto.dir/EpollPoller.o
libevproto.a: CMakeFiles/evproto.dir/eventloop.o
libevproto.a: CMakeFiles/evproto.dir/EventLoopThread.o
libevproto.a: CMakeFiles/evproto.dir/EventLoopThreadPool.o
libevproto.a: CMakeFiles/evproto.dir/evproto.o
libevproto.a: CMakeFiles/evproto.dir/rpcchannel.o
libevproto.a: CMakeFiles/evproto.dir/rpccontroller.o
libevproto.a: CMakeFiles/evproto.dir/rpcserver.o
libevproto.a: CMakeFiles/evproto.dir/Timestamp.o
libevproto.a: CMakeFiles/evproto.dir/Thread.o
libevproto.a: CMakeFiles/evproto.dir/CurrentThread.o
libevproto.a: CMakeFiles/evproto.dir/CountDownLatch.o
libevproto.a: CMakeFiles/evproto.dir/TcpConnection.o
libevproto.a: CMakeFiles/evproto.dir/TcpClient.o
libevproto.a: CMakeFiles/evproto.dir/Connector.o
libevproto.a: CMakeFiles/evproto.dir/build.make
libevproto.a: CMakeFiles/evproto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libevproto.a"
	$(CMAKE_COMMAND) -P CMakeFiles/evproto.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/evproto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/evproto.dir/build: libevproto.a
.PHONY : CMakeFiles/evproto.dir/build

CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Acceptor.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Channel.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Poller.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/EpollPoller.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/eventloop.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/EventLoopThread.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/EventLoopThreadPool.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/evproto.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/rpcchannel.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/rpccontroller.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/rpcserver.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Timestamp.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Thread.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/CurrentThread.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/CountDownLatch.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/TcpConnection.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/TcpClient.o.requires
CMakeFiles/evproto.dir/requires: CMakeFiles/evproto.dir/Connector.o.requires
.PHONY : CMakeFiles/evproto.dir/requires

CMakeFiles/evproto.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/evproto.dir/cmake_clean.cmake
.PHONY : CMakeFiles/evproto.dir/clean

CMakeFiles/evproto.dir/depend:
	cd /usr/local/evproto-master/evproto && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/evproto-master/evproto /usr/local/evproto-master/evproto /usr/local/evproto-master/evproto /usr/local/evproto-master/evproto /usr/local/evproto-master/evproto/CMakeFiles/evproto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/evproto.dir/depend

