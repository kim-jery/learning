#include <iostream>
#include <exception>
#include <array>
#include <functional>
#include <algorithm>
#include <tuple>
#include "../include/utility.hpp"
#include "../include/profile.hpp"
#include "../include/capabilities.hpp"
#include "../include/http_client.hpp"
#include "test_env.hpp"

namespace kjr::learning::test::web_driver {

namespace wd = kjr::learning::web_driver;
using test_case = std::pair<std::string, std::function<void()>>;

template<std::size_t Size>
using test_suite = std::array<test_case, Size>;

test_case test_make_string()
{
    return { __func__, []() -> void {
        {
            auto const string{ wd::make_string("foo", "bar") };
            if (string != "foobar") {
                throw std::runtime_error{ wd::make_string<' '>(string, "does not match foobar") };
            }
        }
        {
            auto const string{ wd::make_string<':'>("foo", "bar") };
            if (string != "foo:bar") {
                throw std::runtime_error{ wd::make_string<' '>(string, "does no match foo:bar") };
            }
        }
    } };
}

test_case test_generate_uuids()
{
    return { __func__, []() -> void {
        auto previous{ wd::generate_uuid() };
        for (std::size_t i{ 0 }; i < 100; ++i) {
            auto const current{ wd::generate_uuid() };
            if (current == previous) {
                throw std::runtime_error{ wd::make_string<' '>("uuid", current, previous, "matches") };
            }
            previous = current;
        }
    } };
}

test_case test_profile_generation()
{
    return { __func__, []() -> void {
        {

            std::filesystem::path profile_dir_which_must_be_removed{};
            {
                wd::profile profile{ test::web_driver::profile_dir };
                auto const profile_move{ std::move(profile) };
                if (!std::filesystem::exists(profile_move.path())) {
                    throw std::runtime_error{ wd::make_string<' '>("Temp profile", profile_move.path(), "must exist") };
                }
                profile_dir_which_must_be_removed = profile_move.path();
            }

            if (std::filesystem::exists(profile_dir_which_must_be_removed)) {
                throw std::runtime_error{ wd::make_string<' '>("Temp profile", profile_dir_which_must_be_removed, "must not exist") };
            }
        }
        {
            wd::profile profile{};
            {
                wd::profile profile_to_move{ test::web_driver::profile_dir };
                profile = std::move(profile_to_move);
            }
            if (!std::filesystem::exists(profile.path())) {
                throw std::runtime_error{
                wd::make_string<' '>("Profile at", profile.path(), " life must be extended outside of the scope of the original profiles")
                };
            }
        }
    } };
}

test_case test_firefox_capabilities_http_client()
{
    return {__func__, []() -> void {
        wd::firefox_capabilities capabilities {"4444", test::web_driver::firefox_binary, {}};
        wd::http_client client {};
        auto session {wd::make_http_session(client, "127.0.0.1", "4444")};
        session.send({wd::http::verb::get, "/status", 11});
    }};
}

template<std::size_t Size>
void execute_test_suite(test_suite<Size> const& suite)
{
    std::for_each(std::cbegin(suite), std::cend(suite), [](auto const& test) -> void {
        auto const& [name, callable] = test;
        try {
            callable();
            std::cout << name << " passed\n";
        } catch (std::runtime_error const& e) {
            std::cout << name << " failed. Exception message :\n";
            std::cout << e.what();
        }
    });
}

}

int main()
{
    namespace test = kjr::learning::test::web_driver;

    std::array suite{
    test::test_make_string(),
    test::test_generate_uuids(),
    test::test_profile_generation(),
    test::test_firefox_capabilities_http_client()
    };

    test::execute_test_suite(suite);

    return 0;
}