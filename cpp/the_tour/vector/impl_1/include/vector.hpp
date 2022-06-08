#ifndef THE_TOUR_VECTOR_HPP
#define THE_TOUR_VECTOR_HPP
#pragma once

#include <initializer_list>
#include <ostream>

namespace kjr::learning::vector_impl_1 {

class vector final
{

private:
    int m_size {};
    int m_capacity {};
    double* m_container {nullptr};

public:
    vector() = default;
    explicit vector(int);
    vector(std::initializer_list<double>);
    vector (vector const&);
    vector (vector&&) noexcept;
    ~vector();

    vector& operator =(vector const&);
    vector& operator =(vector&&) noexcept ;
    double& operator [](int);
    double operator [](int) const;
    bool operator ==(vector const&) const;

    [[nodiscard]] double* begin() const;
    [[nodiscard]] double* end() const;
    [[nodiscard]] double const* cbegin() const;
    [[nodiscard]] double const* cend() const;

    [[nodiscard]] int size() const noexcept;
    [[nodiscard]] int capacity() const noexcept;
    void resize(int);
    void push_back(double);

};

}


#endif //THE_TOUR_VECTOR_HPP
