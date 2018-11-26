cmake_minimum_required(VERSION 3.10)

project(easy-mp VERSION 0.0.0.0)

option(TESTS "whether needs to build tests" ON)

set(PUBLIC_HEADERS src/type_list.h)

add_library(${PROJECT_NAME} INTERFACE)

set(ALL_SOURCES_FOR_STYLE_CORRECTION ${PUBLIC_HEADERS})

include(ClangFormat.cmake)
CODE_STYLE_CORRECTION("${ALL_SOURCES_FOR_STYLE_CORRECTION}")

if (TESTS)

    find_package(GTest REQUIRED)

    enable_testing()

    add_subdirectory("test")

endif()