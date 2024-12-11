cmake_minimum_required(VERSION 3.0)
project (Task2 C)
set(CMAKE_C_STANDART 99)

find_package(SQLite3 REQUIRED)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

set(SOURCES main.c bdfile.c data.c hist.c sqlite3.c)
set(HEADERS bdfile.h data.h hist.h sqlite3.h)

add_executable(Task2 ${SOURCES})

