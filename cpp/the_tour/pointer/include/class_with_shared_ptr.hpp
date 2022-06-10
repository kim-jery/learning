#ifndef THE_TOUR_CLASS_WITH_SHARED_PTR_HPP
#define THE_TOUR_CLASS_WITH_SHARED_PTR_HPP
#pragma once

#include <memory>
#include <iostream>

namespace kjr::learning::pointer {

template<class Value_Contained>
class class_with_shared_ptr final
{

private:
    std::shared_ptr<Value_Contained> m_value;

public:
    explicit class_with_shared_ptr(std::shared_ptr<Value_Contained> value):
        m_value {value} {}

    void increase_value()
    {
        ++(*m_value);
    }

    void show_value() const
    {
        std::cout << "Value contained into the shared_ptr has now a value of " << *m_value << '\n';
    };

};

}

#endif //THE_TOUR_CLASS_WITH_SHARED_PTR_HPP
