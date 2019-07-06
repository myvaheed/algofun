cmake_minimum_required(VERSION 3.12)

project(algofun)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.65.1 COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(test tests/test.cpp src/expl_instance.cpp src/parser.cpp src/sort.cpp)
    target_link_libraries(test ${Boost_LIBRARIES})
endif()