#ifndef THE_TOUR_RAII_HPP
#define THE_TOUR_RAII_HPP
#pragma once

#include <string_view>

namespace kjr::learning::raii {

class raii final
{

private:
    std::string_view m_name;

public:
    explicit raii(std::string_view);
    raii(raii const&) = delete;
    raii(raii&&) = delete;
    ~raii();

public:
    raii operator =(raii const&) = delete;
    raii operator =(raii&&) = delete;

public:
    void output() const;

};

}

#endif //THE_TOUR_RAII_HPP
