#include "./../include/vector.hpp"
#include <algorithm>
#include <format>

using namespace kjr::learning::vector_impl_1;

vector::vector(int size):
    m_size {size},
    m_capacity {size},
    m_container {new double[m_capacity]}
{
    std::fill(m_container, m_container + m_capacity, double{});
}

vector::vector(std::initializer_list<double> values):
    m_size {static_cast<int>(values.size())},
    m_capacity {m_size},
    m_container {new double[m_size]}
{
    std::copy(std::cbegin(values), std::cend(values), m_container);
}

vector::vector(vector const& vector):
    m_size {vector.m_size},
    m_capacity {vector.m_capacity},
    m_container {new double[m_capacity]}
{
    std::copy(vector.m_container, vector.m_container + m_capacity, m_container);

    std::cout << std::format("Vector with {} elements has been copied", m_capacity) << " into " << this << '\n';
}

vector::vector(vector&& vector) noexcept:
    m_size {vector.m_size},
    m_capacity {vector.m_capacity},
    m_container {vector.m_container}
{
    vector.m_container = nullptr;
    vector.m_size = 0;
    vector.m_capacity = 0;

    std::cout << std::format("Vector with {} elements has been moved", m_capacity) << " into " << this << '\n';
}

vector::~vector()
{
    delete[] m_container;
}

vector& vector::operator =(vector const& vector)
{
    if (&vector == this) {
        return *this;
    }

    m_size = vector.m_size;
    m_capacity = vector.m_capacity;
    m_container = new double[m_capacity];
    std::copy(vector.m_container, vector.m_container + m_capacity, m_container);

    return *this;
}

vector& vector::operator =(vector&& vector) noexcept
{
    m_size = vector.m_size;
    m_capacity = vector.m_capacity;
    m_container = vector.m_container;

    vector.m_size = 0;
    vector.m_capacity = 0;
    vector.m_container = nullptr;

    return *this;
}

double& vector::operator[](int index)
{
    return m_container[index];
}

double vector::operator[](int index) const
{
    return m_container[index];
}

bool vector::operator==(const vector& vector) const
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

double* vector::begin() const
{
    return m_container;
}

double* vector::end() const
{
    return m_container + m_capacity;
}

double const* vector::cbegin() const
{
    return m_container;
}

double const* vector::cend() const
{
    return m_container + m_capacity;
}

int vector::size() const noexcept
{
    return m_size;
}

int vector::capacity() const noexcept
{
    return m_capacity;
}

void vector::resize(int new_size)
{
    double* new_container {new double[new_size]};

    std::cout << "Old container at " << m_container << " copied its content into " << new_container << " due to resize\n";

    std::copy(m_container, m_container + m_size, new_container);
    delete[] m_container;
    std::fill(new_container + m_size, new_container + new_size, double{});
    m_capacity = new_size;
    m_container = new_container;
}

void vector::push_back(double value)
{
    if (m_size == m_capacity) {
        resize((m_capacity + 1) * 2);
    }

    m_container[m_size] = value;
    ++m_size;
}
