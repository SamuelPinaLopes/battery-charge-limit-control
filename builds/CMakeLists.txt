cmake_minimum_required(VERSION 3.16)

project(Battery_Charge_Limit)

set(CMAKE_CXX_STANDARD 20)

add_executable(battery_limit_manager
    ../src/bset.cpp
    ../src/param/parameters.cpp
    ../src/param/param_util/util.cpp
    ../src/util/utilities.cpp
)
