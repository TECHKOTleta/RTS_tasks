cmake_minimum_required(VERSION 3.0)
project (App C)
set(CMAKE_C_STANDART 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMEMCACHED REQUIRED libmemcached)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

set(SOURCES app.c hist.c dbfile.c)
set(HEADERS hist.h dbfile.h)
add_executable(App ${SOURCES})

include_directories($CMAKE_CURRENT_SOURCE_DIR)
include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${LIBMEMCACHED_INCLUDE_DIRS})

target_link_libraries(App ${LIBMEMCACHED_LIBRARIES})
target_link_libraries(App ${SQLITE3_LIBRARIES})
target_link_libraries(App m)