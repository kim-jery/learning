#include <algorithm>

#include "../include/capabilities.hpp"

namespace kjr::learning::web_driver {

capabilities::capabilities(std::filesystem::path&& binary, std::optional<profile>&& profile, std::initializer_list<std::string> args):
m_binary{ std::move(binary) },
m_profile{ std::move(profile) },
m_args{ args }
{
    if (m_profile) {
        m_args.emplace_back("-profile");
        m_args.emplace_back(m_profile->path().string());
    }
}

void tag_invoke(boost::json::value_from_tag, boost::json::value& json, capabilities const& capabilities)
{
    json = { { "capabilities", { { "firstMatch", { {
                                                   { "browserName", capabilities.get_browser_name() },
                                                   { capabilities.get_options_identifier(), { { "binary", capabilities.m_binary.string() },
                                                                                              { "args", capabilities.m_args }
                                                   } }
                                                   } } }
    } }
    };
}

std::string firefox_capabilities::get_options_identifier() const
{
    return "moz:firefoxOptions";
}

std::string firefox_capabilities::get_browser_name() const
{
    return "firefox";
}

std::string msedge_capabilities::get_options_identifier() const
{
    return "ms:edgeOptions";
}

std::string msedge_capabilities::get_browser_name() const
{
    return "msedge";
}
}