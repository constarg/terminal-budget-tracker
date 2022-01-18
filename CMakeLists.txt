cmake_minimum_required(VERSION 3.18)
project(budget-tracker C)

set(CMAKE_C_STANDARD 99)

add_executable(budget-tracker main.c commands/commands.c commands/include/commands.h tools/tracker_file.c tools/include/tracker_file.h)

include_directories(
	commands/include
	tools/include
)
