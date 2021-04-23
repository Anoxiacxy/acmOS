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
include CMakeFiles/kernel.img.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kernel.img.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kernel.img.dir/flags.make

# Object files for target kernel.img
kernel_img_OBJECTS =

# External object files for target kernel.img
kernel_img_EXTERNAL_OBJECTS = \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/asm/CMakeFiles/acmOS_spr21-asm.dir/boot.S.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/CMakeFiles/acmOS_spr21-arch.dir/main.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/common/CMakeFiles/acmOS_spr21-common.dir/lock.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/common/CMakeFiles/acmOS_spr21-common.dir/printk.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/common/CMakeFiles/acmOS_spr21-common.dir/uart.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/common/CMakeFiles/acmOS_spr21-common.dir/kernelvec.S.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/common/CMakeFiles/acmOS_spr21-common.dir/string.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o" \
"/home/anoxiacxy/Desktop/acmOS-riscv-master/build/kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o"

kernel.img: kernel/asm/CMakeFiles/acmOS_spr21-asm.dir/boot.S.o
kernel.img: kernel/CMakeFiles/acmOS_spr21-arch.dir/main.c.o
kernel.img: kernel/common/CMakeFiles/acmOS_spr21-common.dir/lock.c.o
kernel.img: kernel/common/CMakeFiles/acmOS_spr21-common.dir/printk.c.o
kernel.img: kernel/common/CMakeFiles/acmOS_spr21-common.dir/uart.c.o
kernel.img: kernel/common/CMakeFiles/acmOS_spr21-common.dir/kernelvec.S.o
kernel.img: kernel/common/CMakeFiles/acmOS_spr21-common.dir/string.c.o
kernel.img: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/start.c.o
kernel.img: kernel/boot/CMakeFiles/acmOS_spr21-boot.dir/kernelvec.S.o
kernel.img: CMakeFiles/kernel.img.dir/build.make
kernel.img: CMakeFiles/kernel.img.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anoxiacxy/Desktop/acmOS-riscv-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking C executable kernel.img"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kernel.img.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kernel.img.dir/build: kernel.img

.PHONY : CMakeFiles/kernel.img.dir/build

CMakeFiles/kernel.img.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kernel.img.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kernel.img.dir/clean

CMakeFiles/kernel.img.dir/depend:
	cd /home/anoxiacxy/Desktop/acmOS-riscv-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anoxiacxy/Desktop/acmOS-riscv-master /home/anoxiacxy/Desktop/acmOS-riscv-master /home/anoxiacxy/Desktop/acmOS-riscv-master/build /home/anoxiacxy/Desktop/acmOS-riscv-master/build /home/anoxiacxy/Desktop/acmOS-riscv-master/build/CMakeFiles/kernel.img.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kernel.img.dir/depend
