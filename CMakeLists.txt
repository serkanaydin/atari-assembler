cmake_minimum_required(VERSION 3.17)
project(atari_assembler C)

set(CMAKE_C_STANDARD 99)

add_executable(atari_assembler  new.c functions.h definitions.h)