file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*[^_test].cpp)
file(GLOB_RECURSE TARGET_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

set(TARGET example)

add_library(${TARGET} STATIC ${TARGET_HEADERS} ${TARGET_SOURCES})
target_compile_options(${TARGET} PRIVATE -Werror -Wall -Wextra)
target_include_directories(${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

include(GNUInstallDirs)
install(
    TARGETS ${TARGET}
    EXPORT ${TARGET}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" 
)
install(
    EXPORT ${TARGET}-targets
    FILE ${TARGET}.cmake
    NAMESPACE MyCorp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyCorp
)

clang_format(${TARGET} ${TARGET_SOURCES} ${TARGET_HEADERS})

# Only build test targets with platform native compiler
if(BUILD_TESTS AND NOT CMAKE_CROSSCOMPILING)
    include(GoogleTest)

    set(TEST_TARGET ${TARGET}-unittest)

    file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp)
    clang_format(${TEST_TARGET} ${TEST_SOURCES})

    add_executable(${TEST_TARGET} ${TEST_SOURCES})
    add_dependencies(${TEST_TARGET} googletest)
    target_include_directories(${TEST_TARGET} PRIVATE
        ${EXTERNAL_INSTALL_LOCATION}/include
        $<TARGET_PROPERTY:${TARGET},INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(${TEST_TARGET} ${TARGET} gtest gtest_main pthread)

    gtest_discover_tests(${TEST_TARGET})

    if(ENABLE_COVERAGE)
        setup_target_for_coverage_gcovr_html(
            NAME ${TARGET}-test-coverage
            BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            EXECUTABLE ctest -j ${PROCESSOR_COUNT}
            DEPENDENCIES ${TEST_TARGET}
            EXCLUDE "*_test.cpp"
        )
    endif()
endif()