#include "../include/profile.hpp"
#include "../include/utility.hpp"

namespace kjr::learning::web_driver {

profile::profile(std::filesystem::path path):
m_original_path{ std::move(path) },
m_tmp_path{ std::filesystem::temp_directory_path() / make_string("web_driver_profile_", generate_uuid()) }
{
    if (!std::filesystem::exists(m_original_path)) {
        throw std::runtime_error{ make_string<true>("Directory at", m_original_path, "does not exist") };
    }

    std::filesystem::copy(m_original_path, m_tmp_path, std::filesystem::copy_options::recursive);
}

profile::~profile()
{
    std::filesystem::remove_all(m_tmp_path);
}

std::filesystem::path const& profile::path() const
{
    return m_tmp_path;
}

profile::profile(profile const& profile):
m_original_path{ profile.m_original_path },
m_tmp_path{ std::filesystem::temp_directory_path() / make_string("web_driver_profile_", generate_uuid()) }
{
    std::filesystem::copy(profile.m_tmp_path, m_tmp_path, std::filesystem::copy_options::recursive);
}

}
