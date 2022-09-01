#ifndef KJR_WEB_DRIVER_PROFILE_HPP
#define KJR_WEB_DRIVER_PROFILE_HPP
#pragma once

#include "driver.hpp"
#include <filesystem>

namespace kjr::learning::web_driver {
class driver;

class profile final
{

private:
    friend class driver;

private:
    std::filesystem::path m_origin_path {};
    std::filesystem::path m_tmp_path {};

public:
    explicit profile(std::filesystem::path);
    ~profile();
    profile(profile const&) = delete;
    profile(profile&&) = delete;
    profile& operator =(profile const&) = delete;
    profile& operator =(profile&&) = delete;

};

}


#endif //KJR_WEB_DRIVER_PROFILE_HPP