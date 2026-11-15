cmake_minimum_required(VERSION 3.20)

project(ip_filter_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ip_filter main.cpp)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(ip_tests tests.cpp)
target_link_libraries(ip_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(ip_tests)