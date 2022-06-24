#ifndef THE_TOUR_TRIANGLE_HPP
#define THE_TOUR_TRIANGLE_HPP
#pragma once

#include "./shape.hpp"

namespace kjr::learning::oop::inheritance {

class triangle final : public shape
{

    using shape::shape;

public:
    void draw(std::ostream&) const override;

};

}


#endif //THE_TOUR_TRIANGLE_HPP
