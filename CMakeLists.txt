cmake_minimum_required(VERSION 3.20)
project(ccut VERSION 1.0.0 LANGUAGES CXX)

# Export compile_commands.json for clangd and other tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable exceptions (GCC/Clang only)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
endif()

# Add compile options (GCC/Clang only)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wformat=2
        -Wundef
        -Wduplicated-cond
        -Wlogical-op
        -Wuseless-cast
        -Wzero-as-null-pointer-constant
        -Wold-style-cast
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wnull-dereference
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wformat=2
        -Wundef
        -Wzero-as-null-pointer-constant
        -Wold-style-cast
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wnull-dereference
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # MSVC warning flags
    add_compile_options(
        /W4
        /WX
        /permissive-
        /Zc:__cplusplus
    )
endif()

# Find GTest
find_package(GTest REQUIRED)

# Library target
add_library(ccutlib STATIC
    src/field_extractor.cpp
    src/options.cpp
)

target_include_directories(ccutlib PUBLIC include)

# Executable target
add_executable(ccut
    app/main.cpp
)

target_link_libraries(ccut ccutlib)

# Test target
add_executable(ccut_tests
    tests/test_field_extractor.cpp
    tests/test_options.cpp
)

target_link_libraries(ccut_tests ccutlib GTest::GTest GTest::Main)

# Enable testing
enable_testing()
add_test(NAME ccut_tests COMMAND ccut_tests)

# Set output directories
if(WIN32)
    set_target_properties(ccut ccut_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>
    )
    set_target_properties(ccutlib PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
    )
else()
    set_target_properties(ccut ccut_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    set_target_properties(ccutlib PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )
endif()