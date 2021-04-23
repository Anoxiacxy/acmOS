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
CMAKE_COMMAND = /bin/cmake

# The command to remove a file.
RM = /bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anoxiacxy/Desktop/acmOS-riscv-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anoxiacxy/Desktop/acmOS-riscv-master/build

# Include any dependencies generated for this target.
include kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/depend.make

# Include the progress variables for this target.
include kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/progress.make

# Include the compile flags for this target's objects.
include kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/flags.make

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/flags.make
kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o: ../kernel/boot/start.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anoxiacxy/Desktop/acmOS-riscv-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o"
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot && riscv64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/acmOS_spr21-boot.dir/start.c.o -c /home/anoxiacxy/Desktop/acmOS-riscv-master/kernel/boot/start.c

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/acmOS_spr21-boot.dir/start.c.i"
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot && riscv64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anoxiacxy/Desktop/acmOS-riscv-master/kernel/boot/start.c > CMakeFiles/acmOS_spr21-boot.dir/start.c.i

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/acmOS_spr21-boot.dir/start.c.s"
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot && riscv64-linux-gnu-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anoxiacxy/Desktop/acmOS-riscv-master/kernel/boot/start.c -o CMakeFiles/acmOS_spr21-boot.dir/start.c.s

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/flags.make
kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o: ../kernel/boot/kernelvec.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anoxiacxy/Desktop/acmOS-riscv-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building ASM object kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o"
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot && riscv64-linux-gnu-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o -c /home/anoxiacxy/Desktop/acmOS-riscv-master/kernel/boot/kernelvec.S

acmOS_spr21-boot: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o
acmOS_spr21-boot: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o
acmOS_spr21-boot: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/build.make

.PHONY : acmOS_spr21-boot

# Rule to build all files generated by this target.
kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/build: acmOS_spr21-boot

.PHONY : kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/build

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/clean:
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot && $(CMAKE_COMMAND) -P CMakeFiles/acmOS_spr21-boot.dir/cmake_clean.cmake
.PHONY : kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/clean

kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/depend:
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anoxiacxy/Desktop/acmOS-riscv-master /home/anoxiacxy/Desktop/acmOS-riscv-master/kernel/boot /home/anoxiacxy/Desktop/acmOS-riscv-master/build /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot /home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/depend

