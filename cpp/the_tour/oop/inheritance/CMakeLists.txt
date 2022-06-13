add_library(
    shape
    include/xy_dim.h

    ./include/shape.h

    ./include/square.h
    ./src/square.cpp

    ./include/rectangle.h
    ./src/rectangle.cpp

    ./include/triangle.h
    ./src/triangle.cpp
)

add_executable(inheritance inheritance.cpp)

target_link_libraries(inheritance PRIVATE shape)