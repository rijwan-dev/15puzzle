cmake_minimum_required(VERSION 3.0.0)

project(15Puzzle VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)


# Find ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add executable and link ncurses
add_executable(15Puzzle 
    src/main.cpp
    src/renderer.cpp
    src/game.cpp
    src/board.cpp
    src/tile.cpp
)
target_link_libraries(15Puzzle ${CURSES_LIBRARIES})

# Add a custom target to run the program
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_CURRENT_BINARY_DIR}/15Puzzle
    DEPENDS 15Puzzle
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

