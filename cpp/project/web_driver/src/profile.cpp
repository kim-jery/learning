#include "../include/profile.hpp"

namespace kjr::learning::web_driver {

profile::profile(std::filesystem::path path):
m_original_path{ std::move(path) },
m_tmp_path{ std::filesystem::temp_directory_path() / generate_uuid() }
{
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

}
