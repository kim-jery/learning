#include <string>
#include "./include/array.hpp"
#include <iostream>
#include <algorithm>
#include <string_view>
#include <format>

namespace kjr::learning::array {

template<class String_Type = std::string_view>
class student final
{

private:
    String_Type m_name {};
    std::size_t m_grades {};

public:
    constexpr student() = default;
    constexpr explicit student(String_Type name):
        m_name {name} {}
    constexpr student(String_Type name, std::size_t grades):
        m_name {name},
        m_grades {grades} {}

    friend std::ostream& operator <<(std::ostream& os, student const& student)
    {
        os << std::format("Student {} has grade : {}\n", student.m_name, student.m_grades);

        return os;
    }

    friend std::istream& operator >>(std::istream& is, student& student)
    {
        String_Type name {};
        std::size_t grade {};

        is >> name >> grade;
        student.m_name = std::move(name);
        student.m_grades = grade;

        return is;
    }

};

template<class String_Type>
void print_array(auto&& array)
{
    std::for_each(std::begin(array), std::end(array), [](student<String_Type> const& student) -> void {
        std::cout << student;
    });
}

}

int main()
{
    namespace array = kjr::learning::array;
    using student_view = array::student<std::string_view>;
    using student = array::student<std::string>;

    constexpr static array::array<student_view, 5> students {
        {"Kim", 20},
        {"Guy", 14},
        {"Paul", 11},
        student_view {"Nathan"},
        {"Israel", 15}
    };

    array::print_array<std::string_view>(students);

    constexpr static std::size_t sz {5};
    auto const students_2 {
        []() -> auto {
            std::cout << "Adding 5 students to an array\n";
            array::array<student, sz> students {};
            for (std::size_t i {0}; i < sz; ++i) {
                std::cout << std::format("Adding student {} - name and grade\n", i + 1);
                std::cin >> students[i];
            }

            return students;
        }()
    };

    array::print_array<std::string>(students_2);

    return 0;
}