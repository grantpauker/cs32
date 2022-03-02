cmake_minimum_required(VERSION 3.22)
project(homework3)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

option(G32 "use g32" ON)

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

include_directories(include src)

set(MAP_SOURCES src/test/map_test.cpp)
set(ODD_SOURCES src/test/odd_test.cpp)
set(BAD_SOURCES src/test/bad_test.cpp)
set(THREE_E_SOURCES src/test/3e.cpp)
set(LIST_SOURCES src/test/list_test.cpp)
set(SORTS_SOURCES src/sorts.cpp)
 

add_executable(oddlist ${ODD_SOURCES})
add_executable(badlist ${BAD_SOURCES})
add_executable(oddvector ${ODD_SOURCES})
add_executable(badvector ${BAD_SOURCES})
target_compile_options(oddvector PRIVATE "-DVECTOR")
target_compile_options(badvector PRIVATE "-DVECTOR")

add_executable(3e ${THREE_E_SOURCES})

add_executable(list ${LIST_SOURCES})

add_executable(sorts ${SORTS_SOURCES})
add_executable(map ${MAP_SOURCES})
