#ifndef KJR_THE_TOUR_TRIANGLE_HPP
#define KJR_THE_TOUR_TRIANGLE_HPP
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


#endif //KJR_THE_TOUR_TRIANGLE_HPP
