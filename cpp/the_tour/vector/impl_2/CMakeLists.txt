add_library(
    vector_impl_2_lib
    ./include/vector.h
    ./src/vector.cpp
)

add_executable(vector_impl_2 vector.cpp)
target_link_libraries(vector_impl_2 vector_impl_2_lib)