# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\CLion 2020.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion 2020.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\6122\lab3\p2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\6122\lab3\p2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p2.dir/flags.make

CMakeFiles/p2.dir/Lab3Prob2.cpp.obj: CMakeFiles/p2.dir/flags.make
CMakeFiles/p2.dir/Lab3Prob2.cpp.obj: ../Lab3Prob2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\6122\lab3\p2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p2.dir/Lab3Prob2.cpp.obj"
	"E:\CLion 2020.2\mingw64\bin\g++.exe"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\p2.dir\Lab3Prob2.cpp.obj -c E:\6122\lab3\p2\Lab3Prob2.cpp

CMakeFiles/p2.dir/Lab3Prob2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p2.dir/Lab3Prob2.cpp.i"
	"E:\CLion 2020.2\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\6122\lab3\p2\Lab3Prob2.cpp > CMakeFiles\p2.dir\Lab3Prob2.cpp.i

CMakeFiles/p2.dir/Lab3Prob2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p2.dir/Lab3Prob2.cpp.s"
	"E:\CLion 2020.2\mingw64\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\6122\lab3\p2\Lab3Prob2.cpp -o CMakeFiles\p2.dir\Lab3Prob2.cpp.s

# Object files for target p2
p2_OBJECTS = \
"CMakeFiles/p2.dir/Lab3Prob2.cpp.obj"

# External object files for target p2
p2_EXTERNAL_OBJECTS =

p2.exe: CMakeFiles/p2.dir/Lab3Prob2.cpp.obj
p2.exe: CMakeFiles/p2.dir/build.make
p2.exe: CMakeFiles/p2.dir/linklibs.rsp
p2.exe: CMakeFiles/p2.dir/objects1.rsp
p2.exe: CMakeFiles/p2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\6122\lab3\p2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p2.dir/build: p2.exe

.PHONY : CMakeFiles/p2.dir/build

CMakeFiles/p2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\p2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/p2.dir/clean

CMakeFiles/p2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\6122\lab3\p2 E:\6122\lab3\p2 E:\6122\lab3\p2\cmake-build-debug E:\6122\lab3\p2\cmake-build-debug E:\6122\lab3\p2\cmake-build-debug\CMakeFiles\p2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p2.dir/depend

