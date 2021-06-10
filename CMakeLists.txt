cmake_minimum_required(VERSION 3.17)
project(atari_assembler C)

set(CMAKE_C_STANDARD 99)

add_executable(atari_assembler main.c basicFunctions.h definitions.h syntaxer.h table.h constantFunctions.h initializer.h)