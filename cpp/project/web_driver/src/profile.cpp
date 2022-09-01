#include "../include/profile.hpp"
#include <filesystem>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace kjr::learning::web_driver {

namespace fs = std::filesystem;

profile::profile(fs::path path):
    m_origin_path {std::move(path)},
    m_tmp_path {std::filesystem::temp_directory_path() / boost::lexical_cast<std::string>(boost::uuids::random_generator{}())}
{
    fs::create_directory(m_tmp_path);
    fs::copy(m_origin_path, m_tmp_path, fs::copy_options::recursive);
}

profile::~profile()
{
    fs::remove_all(m_tmp_path);
}

}

