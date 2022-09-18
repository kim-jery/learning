#ifndef KJR_WEB_DRIVER_CAPABILITIES_HPP
#define KJR_WEB_DRIVER_CAPABILITIES_HPP
#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <initializer_list>
#include "profile.hpp"
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <boost/json.hpp>

namespace kjr::learning::web_driver {
class profile;

class firefox_capabilities
{

private:
    std::filesystem::path m_binary {};
    std::vector<std::string> m_args {};
    profile m_profile {};
    boost::asio::io_service m_ios {};
    boost::process::child m_process {};

public:
    firefox_capabilities(std::string&&, std::initializer_list<std::string>);
    firefox_capabilities(std::string&&, std::filesystem::path&&, std::initializer_list<std::string>);
    void set_profile(profile&&);
    friend void tag_invoke(boost::json::value_from_tag, boost::json::value&, firefox_capabilities const&);

};

}

#endif //KJR_WEB_DRIVER_CAPABILITIES_HPP
