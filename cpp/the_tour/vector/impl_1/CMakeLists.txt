add_library(
    vector_impl_1_lib
    ./include/vector.hpp
    ./src/vector.cpp
    ./src/vector_out.cpp
)

add_executable(
    vector_impl_1
    ./vector.cpp
)

target_link_libraries(vector_impl_1 PRIVATE vector_impl_1_lib)