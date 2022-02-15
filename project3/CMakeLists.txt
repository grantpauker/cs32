cmake_minimum_required(VERSION 3.22)
project(project3)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

option(G32 "use g32" OFF)

if(G32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(WARNINGS "-Wall -Wextra -Wno-sign-compare -Werror=return-type -Wno-unknown-pragmas -Werror=vla")
        
        set(STD "-std=c++17")
        set(SAN "-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer")
        set(SAN2 "-fsanitize=bounds")
        
        if(CMAKE_CXX_COMPILER_VERSION MATCHES "^4\\.9.*$")
            unset(SAN2)
            set(STD "-std=c++14")
        elseif(CMAKE_CXX_COMPILER_VERSION MATCHES "^4\\.8.*$")
            unset(SAN)
            unset(SAN2)
            set(STD "-std=c++14")
        elseif(CMAKE_CXX_COMPILER_VERSION MATCHES "^4\\.[3-7].*$")
            unset(SAN)
            unset(SAN2)
            set(STD "-std=c++0x")
        endif()
        set(CMAKE_CXX_FLAGS "${STD} ${SAN} ${SAN2} ${WARNINGS} ${RPATH}")
    endif()
endif()

include_directories(include)
include_directories(/usr/include/GL)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(game ${SOURCES})
target_link_libraries(game glut GL GLU)
