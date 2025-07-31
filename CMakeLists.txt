cmake_minimum_required(VERSION 3.16)

project(CHIP_8)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SDL2 integration
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Define the executable and its sources
add_executable(CHIP_8
        main.cpp
        src/chip-8.cpp
        include/chip-8.hpp
        helpers/type_aliases.hpp
        helpers/fonts.h
        helpers/constants.hpp
        include/chip8_instructions.hpp
        src/chip8_instructions.cpp
        include/chip8_opcode_dispatcher.hpp
        src/chip8_opcode_dispatcher.cpp
        include/platform.hpp
)

# link SDL2
target_link_libraries(CHIP_8 ${SDL2_LIBRARIES})

# Include directories using <...> style (SYSTEM suppresses warnings)
target_include_directories(CHIP_8
        SYSTEM
        PUBLIC
        include
        helpers
)
