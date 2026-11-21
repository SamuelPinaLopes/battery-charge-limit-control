# cmake minimum version required to run this
cmake_minimum_required(VERSION 3.16)

# name of your project
project(Battery_Charge_Limit)

# tell cmake which version of cpp to use
set(CMAKE_CXX_STANDARD 20)

# tell cmake what is the EXECUTABLE NAME FIRST, then FILES INVOLVED in compilation
add_executable(test
    test.cpp
    ../src/param/parameters.cpp
    ../src/param/param_util/util.cpp
    ../src/util/utilities.cpp
)
