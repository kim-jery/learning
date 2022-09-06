#include <boost/json.hpp>
#include <filesystem>
#include <utility>
#include <vector>
#include <tuple>

#include "../include/utility.hpp"
#include "test_env.hpp"
#include "helpers.hpp"
#include "../include/profile.hpp"

namespace kjr::learning::web_driver::test {

namespace wd = kjr::learning::web_driver;
namespace test = wd::test;
namespace json = boost::json;
namespace fs = std::filesystem;

class test_suite
{

public:
    std::vector<std::pair<std::string, std::function<void()>>> m_tests;

public:
    friend std::ostream& operator <<(std::ostream&, test_suite&);

};

std::ostream& operator<<(std::ostream& os, test_suite& test_suite)
{
    for (auto const& [name, test] : test_suite.m_tests) {
        try {
            test();
            os << "Test " << name << " passed\n";
        } catch (std::exception const& e) {
            os << "Test " << name << " did not pass\nException message : " << e.what() << '\n';
        }

        std::cout << "__________________________________\n";
    }

    test_suite.m_tests.clear();

    return os;
}

void test_generate_uuids()
{
    auto previous{ wd::generate_uuid() };

    for (std::size_t i{ 0 }; i < 100; ++i) {
        auto const current{ wd::generate_uuid() };
        test::assert_not_equal(previous, current);
        previous = current;
    }
}

void test_profile()
{
    fs::path dir_should_not_exist_anymore{};
    {
        wd::profile profile{ profile_path };
        auto const to_json{ json::value{ profile } };
        auto const json_v{ json::serialize(to_json) };

        auto const j_dir{ json::parse(json_v).at(0).as_string() };
        auto dir{ fs::path{ std::cbegin(j_dir), std::cend(j_dir) } };
        test::assert_dir_exists(dir);
        dir_should_not_exist_anymore = std::move(dir);
    }

    test::assert_dir_does_not_exist(dir_should_not_exist_anymore);
}

}

int main()
{
    namespace test = kjr::learning::web_driver::test;

    test::test_suite suite{};
    suite.m_tests.emplace_back("Generate UUID", test::test_generate_uuids);
    suite.m_tests.emplace_back("Profile generation", test::test_profile);

    std::cout << suite;
}