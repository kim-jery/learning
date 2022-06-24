#ifndef THE_TOUR_SQUARE_HPP
#define THE_TOUR_SQUARE_HPP
#pragma once

#include "./shape.hpp"

namespace kjr::learning::oop::inheritance {

class square final : public shape
{

    using shape::shape;

public:
    void draw(std::ostream&) const override;

};

}

#endif //THE_TOUR_SQUARE_HPP
