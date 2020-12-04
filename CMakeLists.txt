cmake_minimum_required(VERSION 3.10)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

project(easy-mp VERSION 1.3.0.0)

option(TESTS "whether needs to build tests" ON)

set(PUBLIC_HEADERS
    src/type_list.h
    src/enum.h
    src/containers.h
)

add_library(${PROJECT_NAME} INTERFACE)

# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADERS}")

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}>"
)

set(ALL_SOURCES_FOR_STYLE_CORRECTION ${PUBLIC_HEADERS})

include(ClangFormat.cmake)
CODE_STYLE_CORRECTION("${ALL_SOURCES_FOR_STYLE_CORRECTION}")

if (TESTS)

    find_package(GTest REQUIRED)

    enable_testing()

    add_subdirectory("test")

endif()

foreach (header ${PUBLIC_HEADERS})
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
