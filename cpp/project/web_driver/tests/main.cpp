#include <boost/json.hpp>
#include <filesystem>
#include <utility>
#include <array>
#include <algorithm>
#include <ranges>

#include "../include/utility.hpp"
#include "test_env.hpp"
#include "helpers.hpp"
#include "../include/profile.hpp"

namespace kjr::learning::web_driver::test {

namespace wd = kjr::learning::web_driver;
namespace test = wd::test;
namespace json = boost::json;
namespace fs = std::filesystem;

using test_case = std::pair<std::string, std::function<void()>>;

template<std::size_t Size>
void execute_test_suite(std::array<test_case, Size>&& suite)
{
    constexpr static auto perform_test{ [](test_case const& test_case) -> void {
        auto const& [name, test] = test_case;
        try {
            test();
            std::cout << "Test " << name << " passed\n";
        } catch (std::exception const& e) {
            std::cout << "Test " << name << " did not pass\nException message : " << e.what() << '\n';
        }

        std::cout << "__________________________________\n";
    } };

    std::for_each(std::cbegin(suite), std::cend(suite), perform_test);
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
        test::assert_dir_exists(profile.path());
        dir_should_not_exist_anymore = profile.path();
    }

    test::assert_dir_does_not_exist(dir_should_not_exist_anymore);
}

void test_profile_when_directory_is_not_valid()
{
    assert_exception_thrown([]() -> void {
        profile{ "foo/bar" };
    }, {});
}

void test_make_string()
{
    assert_equal("FooBar ", make_string("Foo", "Bar"));
}

void test_make_string_with_spaces()
{
    assert_equal("Foo Bar", make_string<true>("Foo", "Bar"));
}

}

int main()
{
    namespace test = kjr::learning::web_driver::test;

    test::execute_test_suite<5>(
    {
    test::test_case{ "Generate UUID", test::test_generate_uuids },
    test::test_case{ "Profile generation", test::test_profile },
    test::test_case{ "Profile generation when directory invalid", test::test_profile_when_directory_is_not_valid },
    test::test_case{ "Make String", test::test_make_string },
    test::test_case{ "Make String with spaces", test::test_make_string_with_spaces }
    });

}
