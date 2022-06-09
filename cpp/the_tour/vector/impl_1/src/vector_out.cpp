#include "./../include/vector.hpp"

namespace impl_1 = kjr::learning::vector_impl_1;

std::ostream& impl_1::operator <<(std::ostream& os, vector const& vector)
{
    os << "______________________________\n";
    os << "Container Values\n";
    for (double val : vector) {
        std::cout << val << '\n';
    }
    os << "______________________________\n";

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