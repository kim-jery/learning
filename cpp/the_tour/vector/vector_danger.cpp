#include <iostream>
#ifdef _DEBUG
#include <vector>
#include <format>
#endif

int main()
{
    std::ios_base::sync_with_stdio(false);

#ifndef _DEBUG
    std::cout << "This program can be run only in debug mode\n";
#else
    std::cout << "Never address to a value into a vector... might be resized and the value pointed almost will always point to garbage\n";

    std::vector<int> values {};
    std::cout << std::format("Capacity of the vector is {}\n", values.capacity());
    values.push_back(42);
    std::cout << std::format("Capacity of the vector is {} - Therefore has been resized\n", values.capacity());
    std::cout << "New address of the first value into the vector : [" << &(*std::begin(values)) << "]\n";
    int* value {&values[0]};
    std::cout << "Correct value pointed : " << *value << '\n';
    std::cout << "Address of the value pointed [" << value << "] which should correspond the address of the first value of the vector\n";
    values.push_back(84);
    std::cout << std::format("Capacity of the vector is {} - Therefore has been resized\n", values.capacity());
    std::cout << "New address of the first value into the vector : [" << &(*std::begin(values)) << "] which no longer correspond the pointer address\n";
    std::cout << "Invalid value pointed : " << *value << '\n' ;
#endif

    return 0;
}