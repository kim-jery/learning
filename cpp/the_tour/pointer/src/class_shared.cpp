#include "./../include/class_shared.hpp"
#include <utility>

namespace pointer = kjr::learning::pointer;

pointer::class_shared::class_shared(std::string value):
    m_value {std::move(value)}
{
    std::cout << std::format("Class shared {} has been build\n", m_value);
}

pointer::class_shared::class_shared::~class_shared()
{
    std::cout << std::format("Class shared {} has been destroyed\n", m_value);
}

pointer::class_shared& pointer::class_shared::class_shared::operator ++()
{
    ++m_increased_times;

    return *this;
}
