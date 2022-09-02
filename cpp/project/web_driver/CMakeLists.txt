cmake_minimum_required(VERSION 3.23)
project(web_driver)

set(CMAKE_CXX_STANDARD 20)
if (DEFINED ENV{Boost_INCLUDE_DIR})
    set(Boost_INCLUDE_DIR $ENV{Boost_INCLUDE_DIR})
endif()
if (DEFINED ENV{Boost_LIBRARY_DIR})
    set(Boost_LIBRARY_DIR $ENV{Boost_LIBRARY_DIR})
endif()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_library(driver STATIC
    include/profile.hpp
    include/utility.hpp
    src/profile.cpp
    src/utility.cpp
)
add_library(helpers STATIC
    tests/helpers.hpp
    tests/helpers.cpp
)

add_executable(web_driver main.cpp)
add_executable(web_driver_test tests/main.cpp)
target_link_libraries(web_driver driver ${Boost_LIBRARIES})
target_link_libraries(web_driver_test driver helpers ${Boost_LIBRARIES})
