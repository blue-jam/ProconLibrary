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

# --- Lint targets ---
file(GLOB_RECURSE ALL_SOURCES
    datastructure/*.hpp graph/*.hpp math/*.hpp geometry/*.hpp string/*.hpp misc/*.hpp
    verify/*.cpp verify/src/*.cpp
)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCES}
        COMMENT "Running clang-format on all source files"
    )
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_SOURCES}
        COMMENT "Checking clang-format on all source files"
    )
endif()

find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK}
            --enable=warning,style,performance
            --suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions.txt
            --error-exitcode=1
            --quiet
            ${ALL_SOURCES}
        COMMENT "Running cppcheck on all source files"
    )
endif()

add_custom_target(lint DEPENDS format-check cppcheck)
