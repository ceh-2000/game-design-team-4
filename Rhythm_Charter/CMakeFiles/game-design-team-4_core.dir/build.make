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
include CMakeFiles/game-design-team-4_core.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game-design-team-4_core.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game-design-team-4_core.dir/flags.make

CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o: CMakeFiles/game-design-team-4_core.dir/flags.make
CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o: ../src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o -c /home/david/Desktop/game-design-team-4/src/Game.cpp

CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Desktop/game-design-team-4/src/Game.cpp > CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.i

CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Desktop/game-design-team-4/src/Game.cpp -o CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.s

CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o: CMakeFiles/game-design-team-4_core.dir/flags.make
CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o: ../src/Song.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o -c /home/david/Desktop/game-design-team-4/src/Song.cpp

CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Desktop/game-design-team-4/src/Song.cpp > CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.i

CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Desktop/game-design-team-4/src/Song.cpp -o CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.s

# Object files for target game-design-team-4_core
game__design__team__4_core_OBJECTS = \
"CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o" \
"CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o"

# External object files for target game-design-team-4_core
game__design__team__4_core_EXTERNAL_OBJECTS =

libgame-design-team-4_core.a: CMakeFiles/game-design-team-4_core.dir/src/Game.cpp.o
libgame-design-team-4_core.a: CMakeFiles/game-design-team-4_core.dir/src/Song.cpp.o
libgame-design-team-4_core.a: CMakeFiles/game-design-team-4_core.dir/build.make
libgame-design-team-4_core.a: CMakeFiles/game-design-team-4_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libgame-design-team-4_core.a"
	$(CMAKE_COMMAND) -P CMakeFiles/game-design-team-4_core.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game-design-team-4_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game-design-team-4_core.dir/build: libgame-design-team-4_core.a

.PHONY : CMakeFiles/game-design-team-4_core.dir/build

CMakeFiles/game-design-team-4_core.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game-design-team-4_core.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game-design-team-4_core.dir/clean

CMakeFiles/game-design-team-4_core.dir/depend:
	cd /home/david/Desktop/game-design-team-4/Rhythm_Charter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Desktop/game-design-team-4 /home/david/Desktop/game-design-team-4 /home/david/Desktop/game-design-team-4/Rhythm_Charter /home/david/Desktop/game-design-team-4/Rhythm_Charter /home/david/Desktop/game-design-team-4/Rhythm_Charter/CMakeFiles/game-design-team-4_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game-design-team-4_core.dir/depend
