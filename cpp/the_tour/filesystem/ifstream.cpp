#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <format>
#include <tuple>

namespace kjr::learning::filesystem {

template<bool Shrink = false, class Path>
    requires std::is_same_v<std::filesystem::path, Path> || std::is_same_v<std::string, Path>
std::string file_get_contents(Path const& path)
{
    constexpr static auto read_fp {
        [](std::ifstream&& fp) -> std::string {
            std::string content {};
            std::string buffer {};

            while (std::getline(fp, buffer)) {
                content += std::move(buffer) + '\n';
            }

            if (!content.empty()) {
                content.pop_back();
            }

            if constexpr (Shrink) {
                content.shrink_to_fit();
            }

            return content;
        }
    };

    if constexpr (std::is_same_v<std::filesystem::path, Path>) {
        return read_fp(std::ifstream {path.string()});
    } else {
        return read_fp(std::ifstream {path});
    }
}

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* const argv[])
{
    namespace fs = std::filesystem;
    using kjr::learning::filesystem::file_get_contents;
    namespace chrono = std::chrono;
    using duration_bench = chrono::duration<std::double_t, std::milli>;
    std::vector<std::pair<std::string_view, duration_bench>> benchs {};

    fs::path const path {argv[1]};

    if (!fs::exists(path)) {
        std::cout << "File " << path << " is not valid\n";

        return 0;
    }

    auto const perform {
        [&benchs]<class Callable>(Callable&& callable, std::string_view name) -> void {
            auto const start {chrono::high_resolution_clock::now()};
            callable();
            auto const end {chrono::high_resolution_clock::now()};

            benchs.emplace_back(name, duration_bench {end - start});
        }
    };

    perform([&path]() -> void {
        std::cout << file_get_contents<true>(path) << '\n';
    }, "Path filesystem - Shring = true");

    perform([&argv]() -> void {
        std::cout << file_get_contents<true>(std::string {argv[1]}) << '\n';
    }, "Std string - Shring = true");

    perform([&path]() -> void {
        std::cout << file_get_contents(path) << '\n';
    }, "Path filesystem - Shring = false");

    perform([&argv]() -> void {
        std::cout << file_get_contents(std::string {argv[1]}) << '\n';
    }, "Std string - Shring = false");

    for (auto const& [name, bench] : benchs) {
        std::cout << std::format("{} took : {}\n", name, bench);
    }

    return 0;
}
