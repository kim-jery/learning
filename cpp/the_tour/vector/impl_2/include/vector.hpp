#ifndef KJR_THE_TOUR_VECTOR_H_IMPL_2
#define KJR_THE_TOUR_VECTOR_H_IMPL_2
#pragma once

#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <format>

namespace kjr::learning::vector_impl_2 {

template<class Type>
    requires (std::is_default_constructible_v<Type> && std::is_move_constructible_v<Type>)
class vector final
{

private:
    std::size_t m_size {0};
    std::size_t m_capacity {0};
    std::size_t m_time_resized {0};
    Type* m_container {nullptr};

public:
    vector() = default;

    explicit vector(std::size_t size):
        m_size {size},
        m_capacity {size},
        m_container {new Type[size]}
    {

        for (std::size_t i {0}; i < m_size; ++i) {
            m_container[i] = Type{};
        }
    }

    vector(std::initializer_list<Type> list):
        m_size {list.size()},
        m_capacity {list.size()},
        m_container {new Type[list.size()]}
    {
        std::copy(std::begin(list), std::end(list), m_container);
    }

    vector(vector const& vector):
        m_size {vector.m_size},
        m_capacity {vector.m_capacity},
        m_time_resized {vector.m_time_resized},
        m_container {new Type[vector.m_capacity]}
    {
        std::copy(vector.m_container, vector.m_container + vector.m_capacity, m_container);
    }

    vector(vector&& vector) noexcept:
        m_size {vector.m_size},
        m_capacity {vector.m_capacity},
        m_time_resized {vector.m_time_resized},
        m_container {vector.m_container}
    {
        vector.m_size = 0;
        vector.m_capacity = 0;
        vector.m_time_resized = 0;
        vector.m_container = nullptr;
    }

    ~vector()
    {
        delete[] m_container;
    }

    vector& operator =(vector const&) = delete;

    vector& operator =(vector&&) = delete;

    Type& operator [](std::size_t index)
    {
        return m_container[index];
    }

    Type const& operator [](std::size_t index) const
    {
        return m_container[index];
    }

    Type* begin() const
    {
        return m_container;
    }

    Type* end() const
    {
        return m_container + m_capacity;
    }

    Type const* cbegin() const
    {
        return m_container;
    }

    Type const* cend() const
    {
        return m_container + m_capacity;
    }

    void push_back(Type&& value)
    {
        resize();

        m_container[m_size] = value;
        ++m_size;
    }

    template<class... Args>
    void emplace_back(Args&&... args)
    {
        resize();

        m_container[m_size] = Type {std::forward<Args>(args)...};
        ++m_size;
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] std::size_t capacity() const noexcept
    {
        return m_capacity;
    }

    friend std::ostream& operator <<(std::ostream& os, vector const& vector)
    {
        os << std::format("Vector of {} elements with a capacity of {} has been resized {} times\n",
                vector.m_size,
                vector.m_capacity,
                vector.m_time_resized
            );
        os << "The container is at address " << vector.m_container << '\n';

        return os;
    }

private:
    void resize(std::size_t new_size)
    {
        Type* new_container {new Type[new_size]};
        std::move(m_container, m_container + m_capacity, new_container);
        delete[] m_container;

        m_container = new_container;
        m_capacity = new_size;
    }

    void resize()
    {
        if (m_size == m_capacity) {
            resize((m_capacity + 1) * 2);
            ++m_time_resized;
        }
    }

};

}


#endif //KJR_THE_TOUR_VECTOR_H_IMPL_2
