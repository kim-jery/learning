#include "./std_cout_outputable.hpp"

namespace kjr::learning::concepts {

class [[maybe_unused]] not_ouputable {};

}

int main()
{
    //kjr::learning::concepts::do_output_no_check(kjr::learning::concepts::not_ouputable {}); // 21 lines of error on my compiler just for this error...
    //kjr::learning::concepts::do_output(kjr::learning::concepts::not_ouputable {}); // 3 lines... kinda better :)

    std::cout << "Uncomment one of the errors above...";

    return 0;
}