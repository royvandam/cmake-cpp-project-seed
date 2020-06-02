cmake_minimum_required(VERSION 3.8)

project(ProjectExample)
enable_language(CXX)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

option(BUILD_TOOLS "Build tool binaries" ON)
option(BUILD_TESTS "Build unit test binaries" ON)
option(ENABLE_COVERAGE "Enable code coverage flags" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(clang-format)

if(ENABLE_COVERAGE)
    include(code-coverage)
    append_coverage_compiler_flags()
endif()

set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_STANDARD 17)

# Only build test targets with platform native compiler
if(BUILD_TESTS AND NOT CMAKE_CROSSCOMPILING)
    ENABLE_TESTING()

    include(ExternalProject)
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

    ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
    )
    link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)
endif()

add_subdirectory(library)
add_subdirectory(application)