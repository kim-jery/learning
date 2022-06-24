add_library(
    array_lib
    include/array.hpp
    ./src/array.cpp
)

add_executable(
    array
    array.cpp
)

target_link_libraries(array array_lib)