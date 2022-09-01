#ifndef KJR_THE_TOUR_RECTANGLE_HPP
#define KJR_THE_TOUR_RECTANGLE_HPP
#pragma once

#include "./shape.hpp"

namespace kjr::learning::oop::inheritance {

class rectangle final : public shape
{

   using shape::shape;

public:
    void draw(std::ostream&) const override;

};

}


#endif //KJR_THE_TOUR_RECTANGLE_HPP
