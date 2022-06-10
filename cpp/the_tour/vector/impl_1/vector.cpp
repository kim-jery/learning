#include "./include/vector.hpp"
#include <iostream>

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
    std::cout << doubles;
    doubles.push_back(30);
    std::cout << doubles;

    auto const doubles_2 {std::move(doubles)};
    std::cout << doubles_2;
    auto doubles_3 {doubles_2};

    std::cout << std::boolalpha << (doubles_2 == doubles_3) << " ; Both vec should be equal\n";
    doubles_3.push_back(42);
    std::cout << std::boolalpha << (doubles_2 == doubles_3) << " ; Both vec should not be equal\n";

    int limit {0};
    std::cout << "Number of input to set into the vector at runtime :";
    std::cin >> limit;
    std::cout << "\nEnter your inputs\n";
    double_list double_from_is {};
    vec::ask_for_inputs(double_from_is, limit);
    std::cout << double_from_is;

    return 0;
}