#include <iostream>
#include <memory>
#include "./include/class_with_shared_ptr.hpp"
#include "./include/class_shared.hpp"

int main()
{
    using class_shared = kjr::learning::pointer::class_shared;

    using class_shared_int = kjr::learning::pointer::class_with_shared_ptr<int>;
    using class_shared_class = kjr::learning::pointer::class_with_shared_ptr<class_shared>;

    std::cout << "Few things learned reading this chapter : \n";
    std::cout << "Always use new to declare a pointer\n";

    int const* const value {new int {1}};
    std::cout << "Hello i'm a pointer at " << value << " with value " << *value << '\n';
    delete value;

    std::cout << "And never the mix malloc free... which i'm not supposed to know ^^\n\n";

    std::cout << "Forget how new and delete work... and USE smart ptr from <memory>\n";
    auto const smart_unique_value {std::make_unique<int const>(25)};

    std::cout << "Hello I'm a unique ptr with a value of " << *smart_unique_value << '\n';

    auto const shared_value {std::make_shared<int>(0)};
    class_shared_int class_shared_1 {shared_value};
    class_shared_int class_shared_2 {shared_value};
    class_shared_1.show_value();
    class_shared_1.increase_value();
    class_shared_2.increase_value();
    class_shared_1.show_value();
    class_shared_2.show_value();

    auto const shared_class_into_share_ptr {std::make_shared<kjr::learning::pointer::class_shared>("Hello World!")};
    std::cout << *shared_class_into_share_ptr;

    class_shared_class class_shared_3 {shared_class_into_share_ptr};
    class_shared_class class_shared_4 {shared_class_into_share_ptr};
    class_shared_3.increase_value();
    std::cout << *shared_class_into_share_ptr;
    class_shared_4.increase_value();
    std::cout << *shared_class_into_share_ptr;

    std::cout << "\nShared_ptr <3 - don't need to take care of deleting the underlying pointer ! :)\n";

    return 0;
}