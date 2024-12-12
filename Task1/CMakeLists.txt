cmake_minimum_required(VERSION 3.0)
project (Task1 C)
set(CMAKE_C_STANDART 99)

set(SOURCES main.c hist.c)
set(HEADERS hist.h)

add_executable(Task1 ${SOURCES})

