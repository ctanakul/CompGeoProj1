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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/chainatee/Fall quarter/comp_geo/proj1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/chainatee/Fall quarter/comp_geo/proj1"

# Include any dependencies generated for this target.
include CMakeFiles/Bresenham.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Bresenham.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Bresenham.dir/flags.make

CMakeFiles/Bresenham.dir/bresenham.cpp.o: CMakeFiles/Bresenham.dir/flags.make
CMakeFiles/Bresenham.dir/bresenham.cpp.o: bresenham.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/chainatee/Fall quarter/comp_geo/proj1/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Bresenham.dir/bresenham.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Bresenham.dir/bresenham.cpp.o -c "/home/chainatee/Fall quarter/comp_geo/proj1/bresenham.cpp"

CMakeFiles/Bresenham.dir/bresenham.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bresenham.dir/bresenham.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/chainatee/Fall quarter/comp_geo/proj1/bresenham.cpp" > CMakeFiles/Bresenham.dir/bresenham.cpp.i

CMakeFiles/Bresenham.dir/bresenham.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bresenham.dir/bresenham.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/chainatee/Fall quarter/comp_geo/proj1/bresenham.cpp" -o CMakeFiles/Bresenham.dir/bresenham.cpp.s

CMakeFiles/Bresenham.dir/bresenham.cpp.o.requires:
.PHONY : CMakeFiles/Bresenham.dir/bresenham.cpp.o.requires

CMakeFiles/Bresenham.dir/bresenham.cpp.o.provides: CMakeFiles/Bresenham.dir/bresenham.cpp.o.requires
	$(MAKE) -f CMakeFiles/Bresenham.dir/build.make CMakeFiles/Bresenham.dir/bresenham.cpp.o.provides.build
.PHONY : CMakeFiles/Bresenham.dir/bresenham.cpp.o.provides

CMakeFiles/Bresenham.dir/bresenham.cpp.o.provides.build: CMakeFiles/Bresenham.dir/bresenham.cpp.o

# Object files for target Bresenham
Bresenham_OBJECTS = \
"CMakeFiles/Bresenham.dir/bresenham.cpp.o"

# External object files for target Bresenham
Bresenham_EXTERNAL_OBJECTS =

Bresenham: CMakeFiles/Bresenham.dir/bresenham.cpp.o
Bresenham: CMakeFiles/Bresenham.dir/build.make
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
Bresenham: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
Bresenham: CMakeFiles/Bresenham.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Bresenham"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Bresenham.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Bresenham.dir/build: Bresenham
.PHONY : CMakeFiles/Bresenham.dir/build

CMakeFiles/Bresenham.dir/requires: CMakeFiles/Bresenham.dir/bresenham.cpp.o.requires
.PHONY : CMakeFiles/Bresenham.dir/requires

CMakeFiles/Bresenham.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Bresenham.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Bresenham.dir/clean

CMakeFiles/Bresenham.dir/depend:
	cd "/home/chainatee/Fall quarter/comp_geo/proj1" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/chainatee/Fall quarter/comp_geo/proj1" "/home/chainatee/Fall quarter/comp_geo/proj1" "/home/chainatee/Fall quarter/comp_geo/proj1" "/home/chainatee/Fall quarter/comp_geo/proj1" "/home/chainatee/Fall quarter/comp_geo/proj1/CMakeFiles/Bresenham.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Bresenham.dir/depend

