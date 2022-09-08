#ifndef KJR_WEB_DRIVER_CAPABILITIES_HPP
#define KJR_WEB_DRIVER_CAPABILITIES_HPP
#pragma once

#include <optional>
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

protected:
    std::filesystem::path m_binary{};
    std::optional<profile> m_profile{};
    std::vector<std::string> m_args{};

public:
    capabilities(std::filesystem::path&&, std::optional<profile>&&, std::initializer_list<std::string>);
    friend void tag_invoke(boost::json::value_from_tag, boost::json::value&, capabilities const&);

protected:
    [[nodiscard]] virtual std::string get_options_identifier() const = 0;
    [[nodiscard]] virtual std::string get_browser_name() const = 0;

};

class firefox_capabilities : public capabilities
{
    using capabilities::capabilities;

protected:
    [[nodiscard]] std::string get_options_identifier() const override;
    [[nodiscard]] std::string get_browser_name() const override;

};

class msedge_capabilities : public capabilities
{
    using capabilities::capabilities;

protected:
    [[nodiscard]] std::string get_options_identifier() const override;
    [[nodiscard]] std::string get_browser_name() const override;

};

}

#endif //KJR_WEB_DRIVER_CAPABILITIES_HPP