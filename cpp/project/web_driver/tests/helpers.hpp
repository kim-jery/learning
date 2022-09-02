#ifndef KJR_WEB_DRIVER_HELPERS_HPP
#define KJR_WEB_DRIVER_HELPERS_HPP
#pragma once

#include <utility>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

namespace kjr::learning::web_driver::test {

template<class T>
concept Outputable = requires(T&& value) {
    {std::cout << value};
};

template<class... Parts>
void throw_runtime_error(Parts&&... parts)
{
    std::stringstream ss {};
    ((ss << parts << ' '), ...);

    throw std::runtime_error {ss.str()};
}

template<class T>
    requires requires(T&& lhs, T&& rhs) { lhs != rhs; }
void assert_not_equals(T&& lhs, T&& rhs)
{
    if (std::forward<T>(lhs) == std::forward<T>(rhs)) {
        if constexpr (Outputable<T>) {
            throw_runtime_error("LHS", lhs, "and", rhs, "are equals");
        } else {
            throw_runtime_error("LHS and RHS are equals");
        }
    }
}

}

#endif //KJR_WEB_DRIVER_HELPERS_HPP