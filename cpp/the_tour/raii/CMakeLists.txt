add_library(
    raii_lib
    ./include/raii.hpp
    ./src/raii.cpp
)

add_executable(
    raii
    ./raii.cpp
)

target_link_libraries(raii raii_lib)