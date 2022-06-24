#ifndef THE_TOUR_ARRAY_HPP
#define THE_TOUR_ARRAY_HPP
#pragma once

#include <cstdint>
#include <type_traits>
#include <initializer_list>
#include <algorithm>

namespace kjr::learning::array {

template<class Value_Type, std::uint32_t Size>
    requires (std::is_default_constructible_v<Value_Type>)
class array final
{

public:
    using value_type = Value_Type;

private:
    Value_Type m_container[Size];

public:
    constexpr array()
    {
        std::fill(std::begin(m_container), std::end(m_container), Value_Type{});
    }

    constexpr array(std::initializer_list<Value_Type> values)
    {
        std::copy(std::begin(values), std::end(values), m_container);
    }

    constexpr auto& operator [](std::uint32_t index)
    {
        return m_container[index];
    }

    constexpr auto operator [](std::uint32_t index) const
    {
        return m_container[index];
    }

    constexpr auto begin() const
    {
        return &m_container[0];
    }

    constexpr auto end() const
    {
        return &m_container[0] + Size;
    }

    constexpr auto const* cbegin() const
    {
        return &m_container[0];
    }

    constexpr auto const* cend() const
    {
        return &m_container[0] + Size;
    }

    constexpr auto size() const
    {
        return Size;
    }

};

}

#endif //THE_TOUR_ARRAY_HPP
