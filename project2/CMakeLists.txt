cmake_minimum_required(VERSION 3.22)
project(project2)
 
include_directories(include)
 
set(MAP_SOURCES src/Map.cpp src/main.cpp)
set(SMALLBERG_SOURCES src/Map.cpp src/smallberg.cpp)

add_executable(map ${MAP_SOURCES})
add_executable(smallberg ${SMALLBERG_SOURCES})

target_compile_options(smallberg PRIVATE "-DGRADER")
