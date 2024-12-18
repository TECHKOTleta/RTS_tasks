cmake_minimum_required(VERSION 3.0)
project (Processor C)
set(CMAKE_C_STANDART 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMEMCACHED REQUIRED libmemcached)

set(SOURCES processor.c)
add_executable(Processor ${SOURCES})

include_directories($CMAKE_CURRENT_SOURCE_DIR)
include_directories(${LIBMEMCACHED_INCLUDE_DIRS})

target_link_libraries(Processor ${LIBMEMCACHED_LIBRARIES})
target_link_libraries(Processor m)