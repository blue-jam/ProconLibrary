cmake_minimum_required(VERSION 3.27)
project(ProconLibrary)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

file(GLOB VERIFY_SOURCES verify/*.test.cpp)
file(GLOB VERIFY_SRC_SOURCES verify/src/*.cpp)

add_compile_options(-Wall -Wno-deprecated -Wno-cpp)

foreach(src ${VERIFY_SOURCES} ${VERIFY_SRC_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
endforeach()
