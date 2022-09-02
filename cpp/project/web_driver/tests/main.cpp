#include "../include/utility.hpp";
#include "helpers.hpp"

namespace wd = kjr::learning::web_driver;
namespace test = wd::test;

void test_generate_uuids()
{
    auto previous {wd::generate_uuid()};

    for (std::size_t i {0}; i < 100; ++i) {
        auto current {wd::generate_uuid()};
        test::assert_not_equals(previous, current);
        std::swap(current, previous);
    }
}

int main()
{
    test_generate_uuids();
}