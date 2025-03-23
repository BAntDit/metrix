cmake_minimum_required(VERSION 3.10)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project(metrix VERSION 1.5.0.0)

option(TESTS "whether needs to build tests" ON)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB TEST_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h")

include(ClangFormat.cmake)
set(ALL_FILES_TO_ADJUST_CODESTYLE ${HEADER_FILES} ${TEST_HEADERS})
CODE_STYLE_CORRECTION("${ALL_FILES_TO_ADJUST_CODESTYLE}")

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_subdirectory("tests")

foreach (header ${HEADER_FILES})
install(
    FILES ${header}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
)
endforeach()

install(
    TARGETS ${PROJECT_NAME}
    EXPORT  ${PROJECT_NAME}
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    # PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
)

install(
    EXPORT ${PROJECT_NAME}
    FILE ${PROJECT_NAME}Config.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/CMake
)

export(
    EXPORT ${PROJECT_NAME}
    FILE ${PROJECT_NAME}Config.cmake
)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/CMake"
)
