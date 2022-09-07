#include "helpers.hpp"

namespace kjr::learning::web_driver::test {

void assert_dir_exists(std::filesystem::path const& path)
{
    if (!std::filesystem::is_directory(path)) {
        throw_runtime_error("Directory", path, "does not exist");
    }
}

void assert_dir_does_not_exist(std::filesystem::path const& path)
{
    if (std::filesystem::is_directory(path)) {
        throw_runtime_error("Directory", path, "exists");
    }
}

}