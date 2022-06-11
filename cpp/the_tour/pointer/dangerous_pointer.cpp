#include <iostream>

int main()
{
    int* value {nullptr};

    {
        int* my_ptr {new int{2}};
        value = my_ptr;

        std::cout << *value << '-' << *my_ptr << '\n';
        delete my_ptr;
    }

    std::cout << *value << '\n' << "Garbage has been printed\n";
}
