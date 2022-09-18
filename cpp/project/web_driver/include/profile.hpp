#ifndef KJR_WEB_DRIVER_PROFILE_HPP
#define KJR_WEB_DRIVER_PROFILE_HPP
#pragma once

#include <filesystem>

namespace kjr::learning::web_driver {

class profile final
{

private:
    std::filesystem::path m_origin_path{};
    std::filesystem::path m_path{};
    bool m_moved{ false };

public:
    profile() = default;
    explicit profile(std::filesystem::path&&);
    ~profile();
    profile(profile const&);
    profile(profile&&) noexcept;
    profile& operator=(profile const&) = delete;
    profile& operator=(profile&&) noexcept;
    [[nodiscard]] std::filesystem::path const& path() const;
};

}

#endif //KJR_WEB_DRIVER_PROFILE_HPP
