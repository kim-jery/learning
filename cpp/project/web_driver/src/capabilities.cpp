#include <algorithm>

#include "../include/capabilities.hpp"

namespace kjr::learning::web_driver {

capabilities::capabilities(std::filesystem::path&& binary, std::initializer_list<std::string> args):
m_binary{ std::move(binary) },
m_args{ args }
{}

capabilities::capabilities(std::filesystem::path&& binary, profile const& profile, std::initializer_list<std::string> args):
m_binary{ std::move(binary) },
m_args{ args }
{
    m_args.emplace_back("-profile");
    m_args.emplace_back(profile.path().string());
}

}
