#ifndef KJR_WEB_DRIVER_PROFILE_HPP
#define KJR_WEB_DRIVER_PROFILE_HPP
#pragma once

#include <filesystem>
#include <string_view>

namespace kjr::learning::web_driver {

class profile final
{

private:
    std::filesystem::path m_original_path{};
    std::filesystem::path m_tmp_path{};

public:
    explicit profile(std::filesystem::path);
    ~profile();
    profile(profile const&);
    profile(profile&&) = default;
    profile& operator=(profile const&) = delete;
    profile& operator=(profile&&) = default;
    [[nodiscard]] std::filesystem::path const& path() const;

};

}

#endif //KJR_WEB_DRIVER_PROFILE_HPP
