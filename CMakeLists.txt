cmake_minimum_required(VERSION 3.0)

project(SB2 LANGUAGES CXX)

# Dependencies
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Core library
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE tests CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

add_library(SB2Core STATIC ${headers} ${sources})
set_target_properties(SB2Core PROPERTIES CXX_STANDARD 20)

# Tests
include(GoogleTest)
enable_testing()

add_executable(SB2Tests ${tests})
target_link_libraries(SB2Tests SB2Core GTest::gtest_main)

gtest_discover_tests(SB2Tests)