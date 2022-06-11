#include "./include/square.h"
#include "./include/rectangle.h"
#include <memory>
#include <vector>
#include <iostream>

namespace kjr::learning::oop::inheritance {

enum class shape_type: int
{
    square,
    rectangle,
};

void draw_shapes(std::vector<std::unique_ptr<shape>> const& shapes, std::ostream& os)
{
    for (auto const& shape : shapes) {
        os << "\nSTART OF DRAWING\n";
        shape->draw(os);
        os << "\nEND OF DRAWING\n";
    }
}

std::unique_ptr<shape> make_shape(shape_type type, std::istream& is, std::ostream& os)
{
    int x {};
    int y {};

    switch (type) {
        case shape_type::square:
            os << "Square width:";
            is >> x;
            return std::make_unique<square>(xy_dim {x, 0});
        case shape_type::rectangle:
            os << "Rectangle width and height:";
            is >> x >> y;
            return std::make_unique<rectangle>(xy_dim {x, y});
    }

    throw std::exception{};
}

void show_intro_text()
{
    std::cout << "0 - for a square\n";
    std::cout << "1 - for a rectangle\n";
    std::cout << "-1 (or anything else) - for drawing\n";
}

bool push_shape(std::vector<std::unique_ptr<shape>>& shapes, int choice)
{
    switch (choice) {
        case 0:
            shapes.push_back(make_shape(inheritance::shape_type::square, std::cin, std::cout));
            return true;
        case 1:
            shapes.push_back(make_shape(inheritance::shape_type::rectangle, std::cin, std::cout));
            return true;
        default:
            return false;
    }
}

}

int main()
{
    namespace inheritance = kjr::learning::oop::inheritance;

    int type {};
    std::vector<std::unique_ptr<inheritance::shape>> shapes {};
    inheritance::show_intro_text();
    while (std::cin >> type) {
        if (!inheritance::push_shape(shapes, type)) {
            inheritance::draw_shapes(shapes, std::cout);
            break;
        }
        inheritance::show_intro_text();
    }

    return 0;
}