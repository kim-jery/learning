#ifndef THE_TOUR_RECTANGLE_H
#define THE_TOUR_RECTANGLE_H
#pragma once

#include "./shape.h"

namespace kjr::learning::oop::inheritance {

class rectangle final : public shape
{

   using shape::shape;

public:
    void draw(std::ostream&) const override;
};

}


#endif //THE_TOUR_RECTANGLE_H
