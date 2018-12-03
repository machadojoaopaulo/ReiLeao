cmake_minimum_required(VERSION 3.12)

project(ReiLeao)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.1 COMPONENTS system filesystem iostreams)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(ReiLeao main.cpp AdamsBashford.h AdamsBashfordUnlimited.h AdamsBashfordSinusoidal.h)
    target_link_libraries(ReiLeao ${Boost_LIBRARIES})
endif()