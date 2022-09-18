#ifndef KJR_WEB_DRIVER_UTILITY_HPP
#define KJR_WEB_DRIVER_UTILITY_HPP
#pragma once

#include <sstream>
#include <string>

namespace kjr::learning::web_driver {

std::string generate_uuid();

template<char Separator = '\0', class... Parts>
std::string make_string(Parts&&... parts)
{
    std::stringstream ss{};
    if constexpr (Separator != '\0') {
        ((ss << std::forward<Parts>(parts) << Separator), ...);
        auto str {ss.str()};
        str.pop_back();

        return str;
    } else {
        ((ss << std::forward<Parts>(parts)), ...);
    }

    return ss.str();
}

}

#endif //KJR_WEB_DRIVER_UTILITY_HPP