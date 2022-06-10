#include "./../include/vector.hpp"
#include <algorithm>
#include <format>

namespace impl_1 = kjr::learning::vector_impl_1;

impl_1::vector::vector(int size):
    m_size {size},
    m_capacity {size},
    m_container {new double[m_capacity]}
{
    std::fill(m_container, m_container + m_capacity, double{});
}

impl_1::vector::vector(std::initializer_list<double> values):
    m_size {static_cast<int>(values.size())},
    m_capacity {m_size},
    m_container {new double[m_size]}
{
    std::copy(std::cbegin(values), std::cend(values), m_container);
}

impl_1::vector::vector(vector const& vector):
    m_size {vector.m_size},
    m_capacity {vector.m_capacity},
    m_container {new double[m_capacity]}
{
    std::copy(vector.m_container, vector.m_container + m_capacity, m_container);

    std::cout << std::format("Vector with {} elements has been copied", m_capacity) << " into " << this << '\n';
}

impl_1::vector::vector(vector&& vector) noexcept:
    m_size {vector.m_size},
    m_capacity {vector.m_capacity},
    m_container {vector.m_container}
{
    vector.m_container = nullptr;
    vector.m_size = 0;
    vector.m_capacity = 0;

    std::cout << std::format("Vector with {} elements has been moved", m_capacity) << " into " << this << '\n';
}

impl_1::vector::~vector()
{
    delete[] m_container;
}

double& impl_1::vector::operator[](int index)
{
    return m_container[index];
}

double impl_1::vector::operator[](int index) const
{
    return m_container[index];
}

bool impl_1::vector::operator==(const vector& vector) const
{
    if (vector.size() != m_size || vector.m_capacity != m_capacity) {
        return false;
    }

    for (auto i {0}; i < m_capacity; ++i) {
        if (vector[i] != m_container[i]) {
            return false;
        }
    }

    return true;
}

double* impl_1::vector::begin() const
{
    return m_container;
}

double* impl_1::vector::end() const
{
    return m_container + m_capacity;
}

double const* impl_1::vector::cbegin() const
{
    return m_container;
}

double const* impl_1::vector::cend() const
{
    return m_container + m_capacity;
}

int impl_1::vector::size() const noexcept
{
    return m_size;
}

int impl_1::vector::capacity() const noexcept
{
    return m_capacity;
}

void impl_1::vector::resize(int new_size)
{
    double* new_container {new double[new_size]};

    std::cout << "Old container at " << m_container << " copied its content into " << new_container << " due to resize\n";

    std::copy(m_container, m_container + m_size, new_container);
    delete[] m_container;
    std::fill(new_container + m_size, new_container + new_size, double{});
    m_capacity = new_size;
    m_container = new_container;
}

void impl_1::vector::push_back(double value)
{
    if (m_size == m_capacity) {
        resize((m_capacity + 1) * 2);
    }

    m_container[m_size] = value;
    ++m_size;
}
