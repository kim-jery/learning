add_library(
    shape
    include/xy_dim.hpp

    include/shape.hpp

    include/square.hpp
    ./src/square.cpp

    include/rectangle.hpp
    ./src/rectangle.cpp

    include/triangle.hpp
    ./src/triangle.cpp
)

add_executable(inheritance inheritance.cpp)

target_link_libraries(inheritance PRIVATE shape)