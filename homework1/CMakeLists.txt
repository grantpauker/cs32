cmake_minimum_required(VERSION 3.22)
project(homework1)
 
file(GLOB SOURCES "*.cpp")
 
add_executable(map ${SOURCES})
