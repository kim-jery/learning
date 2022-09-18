#include "../include/profile.hpp"
#include "../include/utility.hpp"

namespace kjr::learning::web_driver {

profile::profile(std::filesystem::path&& path):
m_origin_path{ std::move(path) },
m_path{ std::filesystem::temp_directory_path() / make_string<'_'>("web_driver_profile", generate_uuid()) }
{
    std::filesystem::copy(m_origin_path, m_path, std::filesystem::copy_options::recursive);
}

profile::~profile()
{
    if (!m_moved) {
        std::filesystem::remove_all(m_path);
    }
}

profile::profile(profile const& profile):
m_origin_path{ profile.m_path },
m_path{ std::filesystem::temp_directory_path() / make_string<'_'>("web_driver_profile", generate_uuid()) }
{
    std::filesystem::copy(profile.m_path, m_path, std::filesystem::copy_options::recursive);
}

profile::profile(profile&& profile) noexcept:
m_origin_path{ std::move(profile.m_origin_path) },
m_path{ std::move(profile.m_path) }
{
    profile.m_moved = true;
}

std::filesystem::path const& profile::path() const
{
    return m_path;
}

profile& profile::operator=(profile&& profile) noexcept
{
    std::exchange(m_path, profile.m_path);
    std::exchange(m_origin_path, profile.m_origin_path);
    profile.m_moved = true;

    return *this;
}

}
