cmake_minimum_required(VERSION 3.0)
project (App C)
set(CMAKE_C_STANDART 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HIREDIS REQUIRED hiredis)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

set(SOURCES main.c hist.c bdfile.c)
set(HEADERS hist.h bdfile.h)
add_executable(App ${SOURCES})

include_directories($CMAKE_CURRENT_SOURCE_DIR)
include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${HIREDIS_INCLUDE_DIRS})

target_link_libraries(App ${HIREDIS_LIBRARIES})
target_link_libraries(App ${SQLITE3_LIBRARIES})
target_link_libraries(App m)