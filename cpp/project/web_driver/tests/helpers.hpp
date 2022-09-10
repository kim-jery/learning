#ifndef KJR_WEB_DRIVER_HELPERS_HPP
#define KJR_WEB_DRIVER_HELPERS_HPP
#pragma once

#include <utility>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../include/utility.hpp"

namespace kjr::learning::web_driver::test {

void assert_dir_exists(std::filesystem::path const&);
void assert_dir_does_not_exist(std::filesystem::path const&);

template<class T>
concept Outputable = requires(T&& value) {
    { std::cout << value };
};

template<class T, class U>
concept Same_Type_Comparable = requires(T&& lhs, U&& rhs) {
    { std::forward<T>(lhs) == std::forward<U>(rhs) } -> std::same_as<bool>;
    std::is_same_v<T, U>;
};

template<class... Parts>
void throw_runtime_error(Parts&& ... parts)
{
    throw std::runtime_error{ make_string<true>(std::forward<Parts>(parts)...) };
}

template<class T, class U>
requires Same_Type_Comparable<T, U>
void assert_not_equal(T&& lhs, U&& rhs)
{
    if (std::forward<T>(lhs) == std::forward<U>(rhs)) {
        if constexpr (Outputable<T>) {
            throw_runtime_error("LHS", lhs, "and RHS", rhs, "are equal");
        } else {
            throw_runtime_error("LHS and RHS are equal");
        }
    }
}

template<class T, class U>
void assert_equal(T&& lhs, U&& rhs)
{
    try {
        assert_not_equal(std::forward<T>(lhs), std::forward<U>(rhs));
    } catch (std::runtime_error const& e) {
        throw_runtime_error("!(NOT)", e.what());
    }
}

template<typename Closure>
void assert_exception_thrown(Closure&& closure, std::string&& exception_message = {})
{
    try {
        std::forward<Closure>(closure)();
        throw_runtime_error("Exception MUST be thrown with message", exception_message);
    } catch (std::exception const& e) {
        if (exception_message.empty()) {
            return;
        }
        if (e.what() != exception_message) {
            throw_runtime_error("Exception message", exception_message, "does not correspond to the exception one", e.what());
        }
    }
}

}

#endif //KJR_WEB_DRIVER_HELPERS_HPP
