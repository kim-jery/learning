#include "./include/vector.hpp"
#include <iostream>

namespace kjr::learning::vector_impl_1 {

void show_vec(vector const& vec)
{
    std::cout << "__________________\n";
    for (double value : vec) {
        std::cout << value << '\n';
    }
    std::cout << "__________________\n";
}

}

int main()
{
    std::ios_base::sync_with_stdio(false);

    namespace vec = kjr::learning::vector_impl_1;
    using double_list = vec::vector;

    double_list doubles(2);
    doubles[0] = 1;
    doubles[1] = 2;
    doubles.resize(10);
    doubles.push_back(10);
    doubles.push_back(20);
    doubles[4] = 3;
    vec::show_vec(doubles);
    doubles.push_back(30);
    vec::show_vec(doubles);
    
    auto const doubles_2 {std::move(doubles)};
    vec::show_vec(doubles_2);
    auto const doubles_3 {doubles_2};

    std::cout << std::boolalpha << (doubles_2 == doubles_3) << " ; Both vec should be equal\n";

    return 0;
}