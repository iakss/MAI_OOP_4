cmake_minimum_required(VERSION 3.14)
project(MAI_OOP_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(geometry INTERFACE)

target_include_directories(geometry INTERFACE
    lib
    lib/geometry
    lib/geometry/figures
    lib/geometry/point
    lib/geometry/figure
    lib/geometry/vector_figure
    lib/geometry/figures/octagon
    lib/geometry/figures/square
    lib/geometry/figures/triangle
)

add_library(vector INTERFACE)
target_include_directories(vector INTERFACE
    lib/vector
)

add_executable(octagon_tests tests/figures/octagon.cpp)
target_link_libraries(octagon_tests geometry vector gtest_main)

add_executable(square_tests tests/figures/square.cpp)
target_link_libraries(square_tests geometry vector gtest_main)

add_executable(triangle_tests tests/figures/triangle.cpp)
target_link_libraries(triangle_tests geometry vector gtest_main)

add_executable(vector_tests tests/vector/unit.cpp)
target_link_libraries(vector_tests vector gtest_main)

add_executable(vector_figure_tests tests/vector_figure/unit.cpp)
target_link_libraries(vector_figure_tests geometry vector gtest_main)

include(GoogleTest)
gtest_discover_tests(octagon_tests)
gtest_discover_tests(square_tests)
gtest_discover_tests(triangle_tests)
gtest_discover_tests(vector_tests)
gtest_discover_tests(vector_figure_tests)
