cmake_minimum_required(VERSION 3.22)
project(project1)
 
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(gark ${SOURCES})
