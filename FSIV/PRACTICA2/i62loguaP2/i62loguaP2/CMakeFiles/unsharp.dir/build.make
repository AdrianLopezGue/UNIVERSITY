# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2

# Include any dependencies generated for this target.
include CMakeFiles/unsharp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/unsharp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unsharp.dir/flags.make

CMakeFiles/unsharp.dir/main.cpp.o: CMakeFiles/unsharp.dir/flags.make
CMakeFiles/unsharp.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/unsharp.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unsharp.dir/main.cpp.o -c /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/main.cpp

CMakeFiles/unsharp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unsharp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/main.cpp > CMakeFiles/unsharp.dir/main.cpp.i

CMakeFiles/unsharp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unsharp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/main.cpp -o CMakeFiles/unsharp.dir/main.cpp.s

CMakeFiles/unsharp.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/unsharp.dir/main.cpp.o.requires

CMakeFiles/unsharp.dir/main.cpp.o.provides: CMakeFiles/unsharp.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/unsharp.dir/build.make CMakeFiles/unsharp.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/unsharp.dir/main.cpp.o.provides

CMakeFiles/unsharp.dir/main.cpp.o.provides.build: CMakeFiles/unsharp.dir/main.cpp.o


# Object files for target unsharp
unsharp_OBJECTS = \
"CMakeFiles/unsharp.dir/main.cpp.o"

# External object files for target unsharp
unsharp_EXTERNAL_OBJECTS =

unsharp: CMakeFiles/unsharp.dir/main.cpp.o
unsharp: CMakeFiles/unsharp.dir/build.make
unsharp: /usr/local/lib/libopencv_stitching.so.3.3.0
unsharp: /usr/local/lib/libopencv_superres.so.3.3.0
unsharp: /usr/local/lib/libopencv_videostab.so.3.3.0
unsharp: /usr/local/lib/libopencv_aruco.so.3.3.0
unsharp: /usr/local/lib/libopencv_bgsegm.so.3.3.0
unsharp: /usr/local/lib/libopencv_bioinspired.so.3.3.0
unsharp: /usr/local/lib/libopencv_ccalib.so.3.3.0
unsharp: /usr/local/lib/libopencv_dpm.so.3.3.0
unsharp: /usr/local/lib/libopencv_face.so.3.3.0
unsharp: /usr/local/lib/libopencv_freetype.so.3.3.0
unsharp: /usr/local/lib/libopencv_fuzzy.so.3.3.0
unsharp: /usr/local/lib/libopencv_img_hash.so.3.3.0
unsharp: /usr/local/lib/libopencv_line_descriptor.so.3.3.0
unsharp: /usr/local/lib/libopencv_optflow.so.3.3.0
unsharp: /usr/local/lib/libopencv_reg.so.3.3.0
unsharp: /usr/local/lib/libopencv_rgbd.so.3.3.0
unsharp: /usr/local/lib/libopencv_saliency.so.3.3.0
unsharp: /usr/local/lib/libopencv_stereo.so.3.3.0
unsharp: /usr/local/lib/libopencv_structured_light.so.3.3.0
unsharp: /usr/local/lib/libopencv_surface_matching.so.3.3.0
unsharp: /usr/local/lib/libopencv_tracking.so.3.3.0
unsharp: /usr/local/lib/libopencv_xfeatures2d.so.3.3.0
unsharp: /usr/local/lib/libopencv_ximgproc.so.3.3.0
unsharp: /usr/local/lib/libopencv_xobjdetect.so.3.3.0
unsharp: /usr/local/lib/libopencv_xphoto.so.3.3.0
unsharp: /usr/local/lib/libopencv_shape.so.3.3.0
unsharp: /usr/local/lib/libopencv_photo.so.3.3.0
unsharp: /usr/local/lib/libopencv_calib3d.so.3.3.0
unsharp: /usr/local/lib/libopencv_phase_unwrapping.so.3.3.0
unsharp: /usr/local/lib/libopencv_dnn.so.3.3.0
unsharp: /usr/local/lib/libopencv_video.so.3.3.0
unsharp: /usr/local/lib/libopencv_datasets.so.3.3.0
unsharp: /usr/local/lib/libopencv_plot.so.3.3.0
unsharp: /usr/local/lib/libopencv_text.so.3.3.0
unsharp: /usr/local/lib/libopencv_features2d.so.3.3.0
unsharp: /usr/local/lib/libopencv_flann.so.3.3.0
unsharp: /usr/local/lib/libopencv_highgui.so.3.3.0
unsharp: /usr/local/lib/libopencv_ml.so.3.3.0
unsharp: /usr/local/lib/libopencv_videoio.so.3.3.0
unsharp: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
unsharp: /usr/local/lib/libopencv_objdetect.so.3.3.0
unsharp: /usr/local/lib/libopencv_imgproc.so.3.3.0
unsharp: /usr/local/lib/libopencv_core.so.3.3.0
unsharp: CMakeFiles/unsharp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable unsharp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unsharp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unsharp.dir/build: unsharp

.PHONY : CMakeFiles/unsharp.dir/build

CMakeFiles/unsharp.dir/requires: CMakeFiles/unsharp.dir/main.cpp.o.requires

.PHONY : CMakeFiles/unsharp.dir/requires

CMakeFiles/unsharp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unsharp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unsharp.dir/clean

CMakeFiles/unsharp.dir/depend:
	cd /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2 /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2 /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2 /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2 /home/adrian/Escritorio/PRACTICAS-FSIV/PRACTICA2/i62loguaP2/i62loguaP2/CMakeFiles/unsharp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unsharp.dir/depend

