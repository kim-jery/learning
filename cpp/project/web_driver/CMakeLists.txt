cmake_minimum_required(VERSION 3.23)
project(web_driver)

set(CMAKE_CXX_STANDARD 20)
if (DEFINED ENV{Boost_INCLUDE_DIR})
    message(STATUS "Boost include dir found in env path at $ENV{Boost_INCLUDE_DIR}")
    set(Boost_INCLUDE_DIR $ENV{Boost_INCLUDE_DIR})
endif ()
if (DEFINED ENV{Boost_LIBRARY_DIR})
    message(STATUS "Boost lib dir found in env path at $ENV{Boost_LIBRARY_DIR}")
    set(Boost_LIBRARY_DIR $ENV{Boost_LIBRARY_DIR})
endif ()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(web_driver_include include/utility.hpp include/profile.hpp include/capabilities.hpp include/http_client.hpp include/web_driver.hpp)
set(web_driver_src src/utility.cpp src/profile.cpp src/capabilities.cpp src/http_client.cpp src/web_driver.cpp)

add_library(web_driver_lib ${web_driver_include} ${web_driver_src})

add_executable(driver main.cpp)
add_executable(test tests/main.cpp tests/test_env.hpp)
target_link_libraries(driver ${Boost_LIBRARIES} web_driver_lib)
target_link_libraries(test ${Boost_LIBRAIRIES} web_driver_lib)
