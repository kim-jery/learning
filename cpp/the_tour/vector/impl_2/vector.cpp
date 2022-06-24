#include <iostream>
#include "./include/vector.hpp"
#include <algorithm>
#include <string_view>

namespace kjr::learning::vector_impl_2 {

template<class Value_Type>
void show_vector(vector<Value_Type> const& vector)
{
    std::cout << vector;

    std::cout << "PRINTING CONTENT\n";

    constexpr static auto output {
        [](auto&& value) -> void {
            std::cout << value << '\n';
        }
    };

    std::for_each(std::begin(vector), std::end(vector), output);

    std::cout << "_______________________________\n";
}

class person final
{

private:
    std::string_view m_name {"No Name"};
    std::size_t m_age {0};

public:
    constexpr person() = default;
    constexpr person(std::string_view name, std::size_t age):
        m_name {name},
        m_age {age} {}
    friend std::ostream& operator <<(std::ostream& os, person const& person)
    {
        os << "Person named : " << person.m_name << " is " << person.m_age << " years old\n";

        return os;
    }
};

namespace literal {

constexpr std::size_t operator"" _szt(unsigned long long value)
{
    return static_cast<size_t>(value);
}

}

}

int main()
{
    namespace vec = kjr::learning::vector_impl_2;
    using namespace vec::literal;

    auto vec_1 {vec::vector<int>(10)};
    vec::show_vector(vec_1);

    auto vec_2 {vec::vector<vec::person> {}};
    vec_2.emplace_back("Jean", 45_szt);
    vec_2.emplace_back("Patrick", 78_szt);
    vec::show_vector(vec_2);
    vec_2.emplace_back("John", 12_szt);
    vec_2.emplace_back("Greg", 32_szt);
    vec::show_vector(vec_2);

    auto vec_3 {std::move(vec_2)};
    vec::show_vector(vec_3);

    return 0;
}