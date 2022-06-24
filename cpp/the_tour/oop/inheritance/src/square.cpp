#include "./../include/square.hpp"

void kjr::learning::oop::inheritance::square::draw(std::ostream& os) const
{
    for (auto i {0}; i < m_two_dim.x; ++i) {
        for (auto j {0}; j < m_two_dim.x; ++j) {
            os << ' ' << m_char_draw << ' ';
        }

        os << '\n';
    }
}
