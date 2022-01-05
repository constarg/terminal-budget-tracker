cmake_minimum_required(VERSION 3.18)
project(budget-tracker C)

set(CMAKE_C_STANDARD 99)

add_executable(budget-tracker main.c commands/commands.c commands/include/commands.h)

include_directories(
	commands/include
)
