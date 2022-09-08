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

set(kjr_webdriver_src
    include/profile.hpp
    include/utility.hpp
    include/capabilities.hpp
    src/profile.cpp
    src/utility.cpp
    src/capabilities.cpp
)

set(kjr_webdriver_test_src
    tests/helpers.hpp
    tests/helpers.cpp
)

add_library(web_driver_lib STATIC ${kjr_webdriver_src})
add_library(test_lib STATIC ${kjr_webdriver_test_src})

add_executable(driver main.cpp)
add_executable(web_driver_test tests/main.cpp)
target_link_libraries(driver web_driver_lib ${Boost_LIBRARIES})
target_link_libraries(web_driver_test web_driver_lib test_lib ${Boost_LIBRARIES})
