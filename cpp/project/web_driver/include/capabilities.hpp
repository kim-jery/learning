#ifndef KJR_WEB_DRIVER_CAPABILITIES_HPP
#define KJR_WEB_DRIVER_CAPABILITIES_HPP
#pragma once

#include <string>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <boost/json.hpp>
#include <filesystem>

#include "profile.hpp"

namespace kjr::learning::web_driver {
class profile;

class capabilities
{

public:
    std::filesystem::path m_binary{};
    std::vector<std::string> m_args{};

public:
    capabilities(std::filesystem::path&&, std::initializer_list<std::string>);
    capabilities(std::filesystem::path&&, profile const&, std::initializer_list<std::string>);
    capabilities(capabilities const&) = delete;
    capabilities(capabilities&&) = delete;
    capabilities& operator=(capabilities const&) = delete;
    capabilities& operator=(capabilities&&) = delete;
};

class firefox_capabilities : public capabilities
{
    using capabilities::capabilities;

public:
    [[nodiscard]] constexpr static std::string get_options_identifier()
    {
        return "moz:firefoxOptions";
    }

    [[nodiscard]] constexpr static std::string get_browser_name()
    {
        return "firefox";
    }

};

class msedge_capabilities : public capabilities
{
    using capabilities::capabilities;

public:
    [[nodiscard]] constexpr static std::string get_options_identifier()
    {
        return "ms:edgeOptions";
    }

    [[nodiscard]] constexpr static std::string get_browser_name()
    {
        return "msedge";
    }

};

template<class T>
concept Webdriver_Capabilities = requires() {
    std::is_base_of_v<capabilities, T>;
    { T::get_options_identifier() } -> std::same_as<std::string>;
    { T::get_browser_name() } -> std::same_as<std::string>;
};

template<Webdriver_Capabilities Capabilities>
void tag_invoke(boost::json::value_from_tag, boost::json::value& json, Capabilities const& capabilities)
{
    json = { { "capabilities", { { "firstMatch", { {
                                                   { "browserName", Capabilities::get_browser_name() },
                                                   { Capabilities::get_options_identifier(), { { "binary", capabilities.m_binary.string() },
                                                                                               { "args", capabilities.m_args }
                                                   } }
                                                   } } }
    } }
    };
}

}

#endif //KJR_WEB_DRIVER_CAPABILITIES_HPP
