#include "./../include/rectangle.hpp"

void kjr::learning::oop::inheritance::rectangle::draw(std::ostream& os) const
{
    for (auto i {0}; i < m_two_dim.x; ++i) {
        for (auto j {0}; j < m_two_dim.y; ++j) {
            os << ' ' << m_char_draw << ' ';
        }

        os << '\n';
    }
}
