#ifndef KJR_WEB_DRIVER_UTILITY_HPP
#define KJR_WEB_DRIVER_UTILITY_HPP
#pragma once

#include <string>

namespace kjr::learning::web_driver {

std::string generate_uuid();

template<class... Parts>
std::string make_string(Parts&&... parts)
{
    std::stringstream ss{};
    ((ss << std::forward<Parts>(parts)), ...);

    return ss.str();
}


}

#endif //KJR_WEB_DRIVER_UTILITY_HPP