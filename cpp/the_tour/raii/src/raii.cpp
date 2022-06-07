#include "../include/raii.hpp"
#include <iostream>
#include <format>

using namespace kjr::learning::raii;

raii::raii(std::string_view name):
    m_name {name}
{
    std::cout << std::format("{} has been constructed\n", m_name);
}

raii::~raii()
{
    std::cout << std::format("{} has been destroyed\n", m_name);
}

void raii::output() const
{
    std::cout << std::format("Message from {}\n", m_name);
}
