#include <fstream>
#include <iostream>
#include <string>

int main([[maybe_unused]] int argc, char const* const argv[])
{
    std::ios_base::sync_with_stdio(false);

    std::ifstream file {argv[1]};
    std::string line {};
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    return 0;
}