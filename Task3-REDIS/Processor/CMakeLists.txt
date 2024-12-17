cmake_minimum_required(VERSION 3.0)
project (Processor C)
set(CMAKE_C_STANDART 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HIREDIS REQUIRED hiredis)
include_directories($CMAKE_CURRENT_SOURCE_DIR)

set(SOURCES main.c)
add_executable(Processor ${SOURCES})

include_directories(${HIREDIS_INCLUDE_DIRS})
target_link_libraries(Processor ${HIREDIS_LIBRARIES})