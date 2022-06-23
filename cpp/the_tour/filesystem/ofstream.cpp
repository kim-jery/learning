#include <iostream>
#include <fstream>
#include <string>
#include <format>

namespace kjr::learning::filesystem {

class student final // stupid example I know... not very inspired today
{

private:
    std::string m_name {};
    std::string m_cursus {};

public:
    friend std::istream& operator >>(std::istream&, student&);
    friend std::ofstream& operator <<(std::ofstream&, student const&);
    [[nodiscard]] constexpr bool valid() const;

};

std::istream& operator >>(std::istream& is, student& student)
{
    std::getline(is, student.m_name);
    std::getline(is, student.m_cursus);

    return is;
}

std::ofstream& operator <<(std::ofstream& ofs, student const& student)
{
    ofs << std::format("Student named : {} is in {}\n", student.m_name, student.m_cursus);

    return ofs;
}

constexpr bool student::valid() const
{
    return !m_name.empty();
}

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* const argv[])
{
    {
        std::ofstream fp {argv[1]};
        std::string buffer {};
        std::string content {};
        std::cout << "Write until you want. Enter an empty entry to exit\n";
        while (true) {
            std::getline(std::cin, buffer);
            if (buffer.empty()) {
                break;
            }

            content += std::move(buffer) += '\n';
        }

        fp << content;
    }

    {
        std::ofstream fp {argv[2]};

        std::cout << "Register students\nTo exit push ENTER two times with empty entries\n";
        kjr::learning::filesystem::student student {};

        do {
            std::cout << "Register student (name, cursus)\n";
            std::cin >> student;
            if (!student.valid()) {
                break;
            }

            fp << student;
            std::cout << "Student has been registered\n";
        } while (student.valid());
    }

    return 0;
}