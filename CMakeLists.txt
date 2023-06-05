# CMakeList.txt : CMake project for StringBenchmarks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)
project(p37_ec_win)
set(CMAKE_CXX_STANDARD 17)
# Add source to this project's executable.
add_executable (p37_ec_win "main.cpp" "driver.cpp" "driver.hpp" "ec.cpp" "ec.hpp")
