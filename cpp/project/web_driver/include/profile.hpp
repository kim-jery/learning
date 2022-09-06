#ifndef KJR_WEB_DRIVER_PROFILE_HPP
#define KJR_WEB_DRIVER_PROFILE_HPP
#pragma once

#include <filesystem>
#include <boost/json.hpp>
#include <optional>

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

public:
    friend std::ostream& operator<<(std::ostream&, profile const&);
    friend void tag_invoke(boost::json::value_from_tag, boost::json::value&, profile const&);

};

template<class Path>
requires std::is_convertible_v<Path, std::filesystem::path>
std::optional<profile> make_profile(Path&& path)
{
    return std::optional<profile>{ std::in_place, std::forward<Path>(path) };
}

}

#endif //KJR_WEB_DRIVER_PROFILE_HPP