#include <iostream>
#include <filesystem>
#include <chrono>
#include <vector>

namespace kjr::learning::filesystem {

enum class color
{
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37
};

constexpr std::string color(std::string&& string, color color)
{
    return "\x1B[" + ((std::to_string(static_cast<int>(color))) += 'm').append(string) += "\x1B[0m";
}

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* const argv[])
{
    std::ios_base::sync_with_stdio(false);

    namespace fs = std::filesystem;
    namespace kjr_fs = kjr::learning::filesystem;
    namespace chrono = std::chrono;
    using duration = chrono::duration<std::double_t, std::milli>;

    std::vector<std::pair<std::string_view, duration>> results {};
    results.reserve(2);
    
    constexpr static auto show_dir_measure {
        [](auto&& iterator, std::string_view name) -> auto {
            constexpr static auto prefix_path {
                [](std::filesystem::path const& path) -> auto {
                    return (fs::is_directory(path)) ? kjr_fs::color("[DIRECTORY]\t", kjr_fs::color::red) : kjr_fs::color("[FILE]\t\t", kjr_fs::color::blue);
                }
            };

            auto const start {chrono::high_resolution_clock::now()};
            for (auto const& path : iterator) {
                std::cout << prefix_path(path) << fs::file_size(path) << "\t\t" << path << '\n';
            }
            auto const end {chrono::high_resolution_clock::now()};

            return std::pair {name, duration {end - start}};
        }
    };

    auto const current_directory {fs::path {argv[1]}};

    if (!fs::is_directory(current_directory)) {
        std::cout << "Directory is invalid\n";

        return 0;
    }

    std::cout << kjr_fs::color("[CURRENT LOOK]\n\n", kjr_fs::color::yellow);
    results.push_back(show_dir_measure(fs::directory_iterator {current_directory}, "Simple"));

    std::cout << kjr_fs::color("[RECURSIVE LOOK]\n\n", kjr_fs::color::yellow);
    results.push_back(show_dir_measure(fs::recursive_directory_iterator {current_directory}, "Recursive"));

    for (auto const& [name, time] : results) {
        std::cout << name << " took " << time << " to list\n";
    }

    return 0;
}