cmake_minimum_required(VERSION 3.20)
project(gdextension-sb2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(sb2core SHARED ${SOURCES})

target_include_directories(sb2core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(sb2core PUBLIC godot::cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX src FILES ${SOURCES})
