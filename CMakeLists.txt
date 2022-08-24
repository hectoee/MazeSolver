cmake_minimum_required(VERSION 3.10)

# set the project name
project(Maze_Solver)

file(GLOB_RECURSE SRCS src/*)

# add the executable
add_executable(Maze_Solver ${SRCS})
target_link_libraries(Maze_Solver SDL2 SDL2_ttf SDL2_image)
set(CMAKE_CXX_FLAGS "-g")
