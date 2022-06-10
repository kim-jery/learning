#include "./../include/vector.hpp"
#include <algorithm>

namespace impl_1 = kjr::learning::vector_impl_1;

std::ostream& impl_1::operator <<(std::ostream& os, vector const& vector)
{
    os << "\n______________________________\n";
    os << "Container Values\n";
    std::for_each(std::begin(vector), std::end(vector), [](double value) -> void {
        std::cout << value << '-';
    });
    os << "\n______________________________\n";

    return os;
}

std::istream& impl_1::operator >>(std::istream& is, vector& vector)
{
    double v;
    is >> v;

    vector.push_back(v);

    return is;
}

void impl_1::ask_for_inputs(vector& vector, int limit)
{
    while (limit != vector.size()) {
        std::cin >> vector;
    }
}