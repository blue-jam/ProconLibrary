cmake_minimum_required(VERSION 3.27)
project(ProconLibrary)

set(CMAKE_CXX_STANDARD 14)

include_directories(datastructure)
include_directories(geometry)
include_directories(graph)
include_directories(math)
include_directories(misc)
include_directories(string)
include_directories(verify/common)

add_executable(ProconLibrary
        verify/aojcgl/CGL_1_A/code/main.cc
        verify/aojcgl/CGL_1_A/test/judge.cc
        verify/aojcgl/CGL_1_A/test/validator.cc
        verify/aojcgl/CGL_1_B/code/main.cc
        verify/aojcgl/CGL_1_B/test/judge.cc
        verify/aojcgl/CGL_1_C/code/main.cc
        verify/aojcgl/CGL_2_A/code/main.cc
        verify/aojcgl/CGL_2_B/code/main.cc
        verify/aojcgl/CGL_2_C/code/main.cc
        verify/aojcgl/CGL_2_C/test/judge.cc
        verify/aojcgl/CGL_2_D/code/main.cc
        verify/aojcgl/CGL_2_D/test/judge.cc
        verify/aojcgl/CGL_3_A/code/main.cc
        verify/aojcgl/CGL_3_B/code/main.cc
        verify/aojcgl/CGL_3_C/code/main.cc
        verify/aojcgl/CGL_4_A/code/main.cc
        verify/aojcgl/CGL_4_C/code/main.cc
        verify/aojcgl/CGL_5_A/code/main.cc
        verify/aojcgl/CGL_7_A/code/main.cc
        verify/aojcgl/CGL_7_D/code/main.cc
        verify/aojcgl/CGL_7_E/code/main.cc
        verify/aojcgl/CGL_7_G/code/main.cc
        verify/aojdsl/DSL_2_A/code/main.cc
        verify/aojdsl/DSL_2_B/code/main.cc
        verify/aojgrl/GRL_1_A/code/main.cc
        verify/aojgrl/GRL_1_B/code/main.cc
        verify/aojgrl/GRL_2_A/code/main.cc
        verify/aojgrl/GRL_3_A/code/main.cc
        verify/aojgrl/GRL_3_B/code/main.cc
        verify/aojgrl/GRL_3_C/code/main.cc
        verify/aojgrl/GRL_4_B/code/main.cc
        verify/aojgrl/GRL_5_C/code/main.cc
        verify/datastructure/aoj1351/code/main.cc
        verify/geometry/aoj1279/code/main.cc
        verify/geometry/aoj2402/code/main.cc
        verify/geometry/aoj2402/test/judge.cc
        verify/geometry/aoj2448/code/main.cc
        verify/geometry/aoj2448/test/judge.cc
        verify/src/atc001c.cpp
        verify/src/disco2016qualc.cpp
        verify/src/koj0093.cpp)
