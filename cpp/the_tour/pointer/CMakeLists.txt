add_library(
    class_with_shared_ptr_lib
    ./include/class_with_shared_ptr.hpp
    ./src/class_with_shared_ptr.cpp
    ./include/class_shared.hpp
    ./src/class_shared.cpp
)

add_executable(
    pointer
    ./pointer.cpp
)

add_executable(
    dangerous_pointer
    ./dangerous_pointer.cpp
)

target_link_libraries(pointer PRIVATE class_with_shared_ptr_lib)