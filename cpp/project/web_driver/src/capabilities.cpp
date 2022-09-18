#include "../include/capabilities.hpp"
#include "../include/utility.hpp"

namespace kjr::learning::web_driver {

firefox_capabilities::firefox_capabilities(std::string&& port, std::initializer_list<std::string> args):
m_binary{ boost::process::search_path("firefox").string() },
m_args{ args },
m_process{ make_string<' '>(boost::process::search_path("geckodriver"), "-p", port), boost::process::std_out > boost::process::null, m_ios }
{
    if (m_binary.empty()) {
        throw std::runtime_error{ "No binary found for firefox" };
    }
}

firefox_capabilities::firefox_capabilities(std::string&& port, std::filesystem::path&& binary, std::initializer_list<std::string> args):
m_binary{ std::move(binary) },
m_args{ args },
m_process{ make_string<' '>(boost::process::search_path("geckodriver"), "-p", port), boost::process::std_out > boost::process::null, m_ios }
{}

void firefox_capabilities::set_profile(profile&& profile)
{
    m_args.emplace_back("-profile");
    m_args.emplace_back(profile.path().string());
    m_profile = std::move(profile);
}

void tag_invoke(boost::json::value_from_tag, boost::json::value& json, firefox_capabilities const& capabilities)
{
    json = {
    { "capabilities", {
        {"firstMatch", { {
            { "browserName", "firefox" },
            { "moz:firefoxOptions", {
                { "binary", capabilities.m_binary.string() },
                { "args", capabilities.m_args }
            } } }
        } }
    } }
    };
}

}