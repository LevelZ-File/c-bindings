cmake_minimum_required(VERSION 3.16)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

# Tests
function(add_test_executable name)
    set(TEST_NAME "levelz-test-${name}")

    add_executable("${TEST_NAME}" "src/${name}.c" "src/test.h")
    target_link_libraries("${TEST_NAME}" PRIVATE levelz-c)
    target_include_directories("${TEST_NAME}" PRIVATE "${PROJECT_SOURCE_DIR}/include")

    add_dependencies("${TEST_NAME}" levelz-c)
    add_test(NAME "${name}.h" COMMAND "${TEST_NAME}")

    if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clan`g")
        target_compile_options("${TEST_NAME}" PRIVATE -coverage -lm -w)
        target_link_options("${TEST_NAME}" PRIVATE -coverage)
        target_link_libraries("${TEST_NAME}" PRIVATE m)
    endif()
endfunction()

add_test_executable(coordinate)
add_test_executable(block)
add_test_executable(matrix)
add_test_executable(level)
add_test_executable(levelz)