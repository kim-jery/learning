#ifndef KJR_WEB_DRIVER_PROFILE_HPP
#define KJR_WEB_DRIVER_PROFILE_HPP
#pragma once

#include <filesystem>
#include <optional>
#include <string_view>

#include "../include/utility.hpp"

namespace kjr::learning::web_driver {

class profile final
{

private:
    std::filesystem::path m_original_path{};
    std::filesystem::path m_tmp_path{};

public:
    explicit profile(std::filesystem::path);
    ~profile();
    profile(profile const&) = delete;
    profile(profile&&) = delete;
    profile& operator=(profile const&) = delete;
    profile& operator=(profile&&) = delete;
    [[nodiscard]] std::filesystem::path const& path() const;

};

template<class Path>
requires std::is_convertible_v<Path, std::filesystem::path>
std::optional<profile> make_profile(Path&& path)
{
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error{ make_string("No valid directory fount at ", path) };
    }

    return std::optional<profile>{ std::in_place, std::forward<Path>(path) };
}

}

#endif //KJR_WEB_DRIVER_PROFILE_HPP