cmake_minimum_required(VERSION 3.22)
project(midterm1)

option(G32 "use g32" OFF)

if(G32)
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

#include_directories(include)

set(Q2_SOURCES q2.cpp)
set(Q3_SOURCES q3.cpp)
 
add_executable(q2 ${Q2_SOURCES})
add_executable(q3 ${Q3_SOURCES})
