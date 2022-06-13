#include "./include/square.h"
#include "./include/rectangle.h"
#include "./include/triangle.h"
#include <memory>
#include <vector>
#include <iostream>

namespace kjr::learning::oop::inheritance {

enum class shape_type: int
{
    square,
    rectangle,
    triangle
};

void draw_shapes(std::vector<std::unique_ptr<shape>> const& shapes, std::ostream& os)
{
    for (auto const& shape : shapes) {
        os << "\nSTART OF DRAWING\n";
        shape->draw(os);
        os << "\nEND OF DRAWING\n";
    }
}

std::unique_ptr<shape> make_shape(shape_type type, std::istream& is, std::ostream& os, char draw_char)
{
    int x {0};
    int y {0};

    switch (type) {
        case shape_type::square:
            os << "Square width:";
            is >> x;
            return std::make_unique<square>(xy_dim {x, 0}, draw_char);
        case shape_type::rectangle:
            os << "Rectangle width and height:";
            is >> x >> y;
            return std::make_unique<rectangle>(xy_dim {x, y}, draw_char);
        case shape_type::triangle:
            os << "Triangle height:";
            is >> x;
            return std::make_unique<triangle>(xy_dim {x, 0}, draw_char);
    }

    throw std::exception{};
}

void show_intro_text()
{
    std::cout << "0 - for a square\n";
    std::cout << "1 - for a rectangle\n";
    std::cout << "2 - for a triangle\n";
    std::cout << "-1 (or anything else) - for drawing\n";
}

bool push_shape(std::vector<std::unique_ptr<shape>>& shapes, int choice, char draw_char)
{
    switch (choice) {
        case 0:
            shapes.push_back(make_shape(inheritance::shape_type::square, std::cin, std::cout, draw_char));
            return true;
        case 1:
            shapes.push_back(make_shape(inheritance::shape_type::rectangle, std::cin, std::cout, draw_char));
            return true;
        case 2:
            shapes.push_back(make_shape(inheritance::shape_type::triangle, std::cin, std::cout, draw_char));
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
    char draw_char {};
    std::vector<std::unique_ptr<inheritance::shape>> shapes {};
    std::cout << "Char for display : ";
    std::cin >> draw_char;
    inheritance::show_intro_text();
    while (std::cin >> type) {
        if (!inheritance::push_shape(shapes, type, draw_char)) {
            inheritance::draw_shapes(shapes, std::cout);
            break;
        }
        inheritance::show_intro_text();
    }

    return 0;
}