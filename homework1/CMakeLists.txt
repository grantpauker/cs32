cmake_minimum_required(VERSION 3.22)
project(homework1)
 
include_directories(include)
 
set(MAP_SOURCES src/Map.cpp src/testMap.cpp)
set(CAR_SOURCES src/Map.cpp src/CarMap.cpp src/testCarMap.cpp)
set(NEW_MAP_SOURCES src/newMap.cpp src/testnewMap.cpp)
 
add_executable(map ${MAP_SOURCES})
add_executable(car ${CAR_SOURCES})
add_executable(newmap ${NEW_MAP_SOURCES})
