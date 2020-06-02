file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*[^_test].cpp)
file(GLOB_RECURSE TARGET_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

set(TARGET myapp)

add_executable(${TARGET} ${TARGET_HEADERS} ${TARGET_SOURCES})
target_compile_options(${TARGET} PRIVATE -Werror -Wall -Wextra)
target_include_directories(${TARGET} PRIVATE
    ${EXTERNAL_INSTALL_LOCATION}/include
    $<TARGET_PROPERTY:example,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(${TARGET} example)

include(GNUInstallDirs)
install(
    TARGETS ${TARGET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

clang_format(${TARGET} ${TARGET_SOURCES} ${TARGET_HEADERS})