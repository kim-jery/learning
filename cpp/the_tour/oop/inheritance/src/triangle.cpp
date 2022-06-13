#include "./../include/triangle.h"

void kjr::learning::oop::inheritance::triangle::draw(std::ostream& os) const
{
    auto const height {m_two_dim.x + 1};

    for (auto i {0}; i < height; ++i) {
        for (auto space {height}; space > i; --space) {
            os << ' ';
        }
        for (auto j {i * 2 - 1}; j > 0; --j) {
            os << m_char_draw;
        }
        os << '\n';
    }
}