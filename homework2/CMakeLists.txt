cmake_minimum_required(VERSION 3.22)
project(homework2)
 
include_directories(include)
 
set(MAZE_STACK_SOURCES src/mazestack.cpp src/maze.cpp)
set(MAZE_QUEUE_SOURCES src/mazequeue.cpp src/maze.cpp)
set(EVAL_SOURCES src/Map.cpp src/eval.cpp src/eval_test.cpp)
 
add_executable(stack ${MAZE_STACK_SOURCES})
add_executable(queue ${MAZE_QUEUE_SOURCES})
add_executable(eval ${EVAL_SOURCES})
