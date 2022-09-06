#ifndef KJR_WEB_DRIVER_HELPERS_HPP
#define KJR_WEB_DRIVER_HELPERS_HPP
#pragma once

#include <utility>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>

namespace kjr::learning::web_driver::test {

template<class T>
concept Outputable = requires(T&& value) {
    { std::cout << value };
};

template<class... Parts>
void throw_runtime_error(Parts&& ... parts)
{
    std::stringstream ss{};
    ((ss << std::forward<Parts>(parts) << ' '), ...);

    throw std::runtime_error{ ss.str() };
}

template<class T, class U>
requires requires(T&& lhs, U&& rhs) {
    { lhs == rhs } -> std::same_as<bool>;
    std::is_same_v<T, U>;
}
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

void assert_dir_exists(std::filesystem::path const& path)
{
    if (!std::filesystem::is_directory(path)) {
        throw_runtime_error("Directory", path, "does not exist");
    }
}

void assert_dir_does_not_exist(std::filesystem::path const& path)
{
    if (std::filesystem::is_directory(path)) {
        throw_runtime_error("Directory", path, "exists");
    }
}

}

#endif //KJR_WEB_DRIVER_HELPERS_HPP