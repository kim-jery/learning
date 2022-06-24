#ifndef THE_TOUR_SHAPE_HPP
#define THE_TOUR_SHAPE_HPP
#pragma once

#include "./xy_dim.hpp"
#include <ostream>

namespace kjr::learning::oop::inheritance {

class shape
{

protected:
    xy_dim m_two_dim;
    char m_char_draw {'*'};

public:
    constexpr explicit shape(xy_dim dim):
        m_two_dim {dim} {}
    constexpr shape(xy_dim dim, char char_draw):
        m_two_dim {dim},
        m_char_draw {char_draw} {}
    virtual ~shape() = default;

    virtual void draw(std::ostream&) const = 0;

};

}

#endif //THE_TOUR_SHAPE_HPP
