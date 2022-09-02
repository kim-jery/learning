#include "../include/profile.hpp"
#include "../include/utility.hpp"
#include <boost/json.hpp>

namespace kjr::learning::web_driver {

profile::profile(std::filesystem::path path):
    m_original_path {std::move(path)},
    m_tmp_path {std::filesystem::temp_directory_path() / generate_uuid()}
{
    std::filesystem::copy(m_original_path, m_tmp_path, std::filesystem::copy_options::recursive);
}

profile::~profile()
{
    std::filesystem::remove_all(m_tmp_path);
}

std::ostream& operator<<(std::ostream& os, profile const& profile)
{
    os << profile.m_tmp_path;

    return os;
}

void tag_invoke(boost::json::value_from_tag, boost::json::value& json, profile const& profile)
{
    json = profile.m_tmp_path.string();
}

}
