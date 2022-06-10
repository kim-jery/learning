#ifndef THE_TOUR_CLASS_SHARED_HPP
#define THE_TOUR_CLASS_SHARED_HPP
#pragma once

#include <string>
#include <iostream>
#include <format>

namespace kjr::learning::pointer {

class class_shared final
{

private:
    std::string m_value;
    int m_increased_times {0};

public:
    explicit class_shared(std::string);
    class_shared(class_shared const&) = default;
    class_shared(class_shared&&) = default;
    ~class_shared();

    class_shared& operator =(class_shared const&) = default;
    class_shared& operator =(class_shared&&) = default;
    class_shared& operator ++();
    friend std::ostream& operator <<(std::ostream& os, class_shared const& class_shared) {
        os << std::format("Class shared with string {} has been increased {} times\n",
              class_shared.m_value,
              class_shared.m_increased_times
        );

        return os;
    }

};

}

#endif //THE_TOUR_CLASS_SHARED_HPP
