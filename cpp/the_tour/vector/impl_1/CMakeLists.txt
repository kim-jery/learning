add_library(
    vector_impl_1_lib
    ./vector/impl_1/include/vector.hpp
    ./vector/impl_1/src/vector.cpp
    ./vector/impl_1/src/vector_out.cpp
)

add_executable(
    vector_impl_1
    ./vector/impl_1/vector.cpp
)

target_link_libraries(vector_impl_1 PRIVATE vector_impl_1_lib)