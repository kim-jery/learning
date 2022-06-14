add_library(
    array_lib
    ./include/array.h
    ./src/array.cpp
)

add_executable(
    array
    array.cpp
)

target_link_libraries(array array_lib)