#include "./std_cout_outputable.h"
#include <string>
#include <string_view>

int main ()
{
    namespace kjr = kjr::learning::concepts;
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    kjr::do_output("Hello"s, ',', "Wor"sv, "ld");

    return 0;
}