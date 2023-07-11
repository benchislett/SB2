cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-Wall -Wextra -Werror -Wno-unused-parameter)

project(SB2 LANGUAGES CXX)

# Dependencies
cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
  GDExtension
  GIT_REPOSITORY https://github.com/godotengine/godot-cpp.git
  GIT_TAG godot-4.0-stable
)

FetchContent_MakeAvailable(GDExtension)
FetchContent_MakeAvailable(googletest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Core library
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE tests CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

add_library(SB2Core SHARED ${headers} ${sources})
target_link_libraries(SB2Core PUBLIC godot::cpp)

# Tests
include(GoogleTest)
enable_testing()

add_executable(SB2Tests ${tests})
target_link_libraries(SB2Tests SB2Core GTest::gtest_main)

gtest_discover_tests(SB2Tests)