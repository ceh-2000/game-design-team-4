# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Desktop/game-design-team-4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Desktop/game-design-team-4/Rhythm_Charter

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/bin/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/bin/main.cpp.o: ../bin/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/bin/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/bin/main.cpp.o -c /home/david/Desktop/game-design-team-4/bin/main.cpp

CMakeFiles/main.dir/bin/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/bin/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Desktop/game-design-team-4/bin/main.cpp > CMakeFiles/main.dir/bin/main.cpp.i

CMakeFiles/main.dir/bin/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/bin/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Desktop/game-design-team-4/bin/main.cpp -o CMakeFiles/main.dir/bin/main.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/bin/main.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/bin/main.cpp.o
main: CMakeFiles/main.dir/build.make
main: /usr/lib/libsfml-graphics.so
main: /usr/lib/libsfml-window.so
main: /usr/lib/libsfml-system.so
main: /usr/lib/libsfml-audio.so
main: /usr/lib/libsfml-network.so
main: libgame-design-team-4_core.a
main: /usr/lib/libsfml-graphics.so
main: /usr/lib/libsfml-window.so
main: /usr/lib/libsfml-system.so
main: /usr/lib/libsfml-audio.so
main: /usr/lib/libsfml-network.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/david/Desktop/game-design-team-4/Rhythm_Charter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/game-design-team-4 /home/david/Desktop/game-design-team-4 /home/david/Desktop/game-design-team-4/Rhythm_Charter /home/david/Desktop/game-design-team-4/Rhythm_Charter /home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
