#ifndef THE_TOUR_VECTOR_HPP_IMPL_1
#define THE_TOUR_VECTOR_HPP_IMPL_1
#pragma once

#include <initializer_list>
#include <iostream>

namespace kjr::learning::vector_impl_1 {

class vector final
{

private:
    int m_size {0};
    int m_capacity {0};
    double* m_container {nullptr};

public:
    vector() = default;
    explicit vector(int);
    vector(std::initializer_list<double>);
    vector (vector const&);
    vector (vector&&) noexcept;
    ~vector();

    vector& operator =(vector const&) = delete;
    vector& operator =(vector&&) = delete;
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

std::ostream& operator <<(std::ostream&, vector const&);
std::istream& operator >>(std::istream&, vector&);

void ask_for_inputs(vector&, int);


}

#endif //THE_TOUR_VECTOR_HPP_IMPL_1
