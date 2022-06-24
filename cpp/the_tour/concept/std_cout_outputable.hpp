#ifndef THE_TOUR_STD_COUT_OUTPUTABLE_HPP
#define THE_TOUR_STD_COUT_OUTPUTABLE_HPP
#pragma once

#include <iostream>

namespace kjr::learning::concepts {

template<class T>
concept Std_Cout_Outputable = requires(T&& val)
{
    { std::cout << val };
};

template<Std_Cout_Outputable... T>
void do_output(T&&... vals)
{
    (std::cout << ... << vals) << '\n';
}

template<class... T>
void do_output_no_check(T&&... vals)
{
    (std::cout << ... << vals) << '\n';
}

}

#endif //THE_TOUR_STD_COUT_OUTPUTABLE_HPP
