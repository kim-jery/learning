#include <iostream>
#include "./include/raii.hpp"
#include <memory>

namespace kjr::learning::raii {

void output_separator()
{
    std::cout << "_____________________________\n";
}

}

int main()
{
    std::ios_base::sync_with_stdio(false);

    namespace raii = kjr::learning::raii;

    raii::raii const r1 {"RAII main stack"}; // this will be destroyed at the end of main
    static raii::raii const r2 {"RAII main stack STATIC"}; // this will be destroyed at the end of the program
    [[maybe_unused]] raii::raii const* const r3 {new raii::raii {"RAII main stack RAW POINTER NEVER DELETED (MEMORY LEAK)"}}; // this will never be destroyed ; memory leak
    raii::raii const* const r4 {new raii::raii {"RAII main stack RAW POINTER (NO MEMORY LEAK) if no exception :)"}}; // this will be destroyed when delete is called
    auto const raii5 {std::make_unique<raii::raii const>("RAII main stack UNIQUE_PTR")}; // this will be destroyed at the end of main
    auto const raii6 {std::make_shared<raii::raii const>("RAII main stack SHARED_PTR")}; // this will be destroyed at the end the program

    std::shared_ptr<raii::raii const> raii_4_ptr {nullptr}; // container for raii_4 ; will be destroyed at the end of main

    raii::output_separator();

    std::cout << "START OF SUB STACK 1\n";
    {
        std::shared_ptr<raii::raii const> raii_1_1_ptr {nullptr}; // container of raii_4 of substack 1-1 ; will be destroyed of the end of this stack
        std::cout << "START OF SUB STACK 1-1\n";
        {
            raii::output_separator();

            raii::raii raii_1 {"RAII stack 1-1"}; // this will be destroyed at the end of this stack
            static raii::raii raii_2 {"RAII stack 1-1 STATIC"}; // this will be destroyed at the end of the program
            auto const raii_3 {std::make_unique<raii::raii const>("RAII stack 1-1 UNIQUE_PTR")}; // this will be destroyed at the end of this stack
            auto raii_4 {std::make_shared<raii::raii const>("RAII stack 1-1 SHARE_PTR")}; // should be destroyed at the end this stack, but will be extended
            raii_1_1_ptr = std::move(raii_4);

            raii::output_separator();
        }
        std::cout << "END OF SUB STACK 1-1\n";

        raii::raii const raii_1 {"RAII stack 1"}; // this will be destroyed at the end of this stack
        static raii::raii const raii_2 {"RAII stack 1 STATIC"}; // this will be destroyed at the end of the program
        auto const raii_3 {std::make_unique<raii::raii const>("RAII stack 1 UNIQUE_PTR")}; // this will be destroyed at the end of this stack
        auto raii_4 {std::make_shared<raii::raii const>("RAII stack 1 SHARE_PTR")}; // should be destroyed at the end this stack, but will be extended
        raii_4_ptr = std::move(raii_4); // increase life of raii_4 outside this stack
        raii_1_1_ptr->output();

        std::cout << "START OF SUB STACK 1-2\n";
        {
            raii::output_separator();
            raii_1_1_ptr->output();

            raii::raii const raii_1_2 {"RAII stack 1-2"}; // this will be destroyed at the end of this stack
            static raii::raii const raii_2_2 {"RAII stack 1-2 STATIC"}; // this will be destroyed at the end of the program
            auto const raii_3_3 {std::make_unique<raii::raii>("RAII stack 1-2 UNIQUE_PTR")}; // this will be destroyed at the end of this stack
            auto const raii_4_4{std::make_shared<raii::raii>("RAII stack 1-2 SHARE_PTR")}; // destroyed at the end this stack

            raii::output_separator();
        }

        std::cout << "END OF SUB STACK 1-2\n";
        raii_1_1_ptr->output();
    }
    std::cout << "END OF SUB STACK 1\n";

    raii::output_separator();

    delete r4;

    raii_4_ptr->output();

    return 0;
}