# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/harrisonbitonti/projects/bioopt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311

# Include any dependencies generated for this target.
include CMakeFiles/bioopt_python.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bioopt_python.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bioopt_python.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bioopt_python.dir/flags.make

CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o: CMakeFiles/bioopt_python.dir/flags.make
CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o: /home/harrisonbitonti/projects/bioopt/src/bindings/bindings.cpp
CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o: CMakeFiles/bioopt_python.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o -MF CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o.d -o CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o -c /home/harrisonbitonti/projects/bioopt/src/bindings/bindings.cpp

CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harrisonbitonti/projects/bioopt/src/bindings/bindings.cpp > CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.i

CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harrisonbitonti/projects/bioopt/src/bindings/bindings.cpp -o CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.s

CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o: CMakeFiles/bioopt_python.dir/flags.make
CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o: /home/harrisonbitonti/projects/bioopt/src/algorithms/sma.cpp
CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o: CMakeFiles/bioopt_python.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o -MF CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o.d -o CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o -c /home/harrisonbitonti/projects/bioopt/src/algorithms/sma.cpp

CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harrisonbitonti/projects/bioopt/src/algorithms/sma.cpp > CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.i

CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harrisonbitonti/projects/bioopt/src/algorithms/sma.cpp -o CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.s

CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o: CMakeFiles/bioopt_python.dir/flags.make
CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o: /home/harrisonbitonti/projects/bioopt/src/core/optimizer.cpp
CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o: CMakeFiles/bioopt_python.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o -MF CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o.d -o CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o -c /home/harrisonbitonti/projects/bioopt/src/core/optimizer.cpp

CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harrisonbitonti/projects/bioopt/src/core/optimizer.cpp > CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.i

CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harrisonbitonti/projects/bioopt/src/core/optimizer.cpp -o CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.s

# Object files for target bioopt_python
bioopt_python_OBJECTS = \
"CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o" \
"CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o" \
"CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o"

# External object files for target bioopt_python
bioopt_python_EXTERNAL_OBJECTS =

/home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so: CMakeFiles/bioopt_python.dir/src/bindings/bindings.cpp.o
/home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so: CMakeFiles/bioopt_python.dir/src/algorithms/sma.cpp.o
/home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so: CMakeFiles/bioopt_python.dir/src/core/optimizer.cpp.o
/home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so: CMakeFiles/bioopt_python.dir/build.make
/home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so: CMakeFiles/bioopt_python.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared module /home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bioopt_python.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/strip /home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so

# Rule to build all files generated by this target.
CMakeFiles/bioopt_python.dir/build: /home/harrisonbitonti/projects/bioopt/build/lib.linux-x86_64-cpython-311/bioopt_python.cpython-311-x86_64-linux-gnu.so
.PHONY : CMakeFiles/bioopt_python.dir/build

CMakeFiles/bioopt_python.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bioopt_python.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bioopt_python.dir/clean

CMakeFiles/bioopt_python.dir/depend:
	cd /home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harrisonbitonti/projects/bioopt /home/harrisonbitonti/projects/bioopt /home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311 /home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311 /home/harrisonbitonti/projects/bioopt/build/temp.linux-x86_64-cpython-311/CMakeFiles/bioopt_python.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bioopt_python.dir/depend

