#pragma once
#include <cstring>
#include <malloc.h>
#include <stdexcept>

namespace gallium {
    template<typename T>
    class Vec {
    public:
        Vec();
        Vec(const T*, size_t size);
        Vec(const Vec&&);

        friend std::ostream& operator<<(std::ostream &os, const Vec &v) {
            os<<"[";
            for (size_t i = 0; i < v.m_Size; i++) {
                os<<v.m_Buffer[i];
                if (i != v.m_Size - 1) {
                    os<<", ";
                }
            }
            os<<"]";
            return os;
        }
        T pop();
        void push(const T&&);
        void insert(size_t, T&&);
        T remove(size_t);
        size_t len();

        T& operator[](size_t);

        ~Vec();

    private:
        T *m_Buffer;
        size_t m_Cap;
        size_t m_Size;

        void increase_cap(size_t);
        T* allocate(size_t);
    };
}

template<typename T>
gallium::Vec<T>::Vec() {
    m_Buffer = allocate(sizeof(T));
    m_Cap = 1;
    m_Size = 0;
}

template<typename T>
gallium::Vec<T>::Vec(const T *src, size_t size) {
    m_Buffer = allocate(sizeof(T) * size);
    m_Cap = size;
    m_Size = size;

    memcpy(m_Buffer, src, sizeof(T) * size);
}

template<typename T>
gallium::Vec<T>::Vec(const Vec<T> &&src) {
m_Buffer = src.m_Buffer;
    m_Cap = src.m_Cap;
    m_Size = src.m_Size;

    src.m_Buffer = nullptr;
    src.m_Cap = 0;
    src.m_Size = 0;
}

template<typename T>
T gallium::Vec<T>::pop() {
    if (m_Size == 0) {
        throw std::runtime_error("Cannot pop from empty Vec");
    }

    T val = m_Buffer[m_Size - 1];
    m_Size--;
    return val;
}

template<typename T>
void gallium::Vec<T>::push(const T &&val) {
    if (m_Size == m_Cap) {
        increase_cap(m_Cap * 2);
    }

    m_Buffer[m_Size] = val;
    m_Size++;
}

template<typename T>
void gallium::Vec<T>::insert(size_t index, T &&val) {
    if (index > m_Size) {
        throw std::runtime_error("Index out of bounds");
    }

    if (m_Size == m_Cap) {
        increase_cap(m_Cap * 2);
    }

    for (size_t i = m_Size; i > index; i--) {
        m_Buffer[i] = m_Buffer[i - 1];
    }

    m_Buffer[index] = val;
    m_Size++;
}

template<typename T>
T gallium::Vec<T>::remove(size_t index) {
    if (index >= m_Size) {
        throw std::runtime_error("Index out of bounds");
    }

    T val = m_Buffer[index];

    for (size_t i = index; i < m_Size - 1; i++) {
        m_Buffer[i] = m_Buffer[i + 1];
    }

    m_Size--;
    return val;
}

template<typename T>
size_t gallium::Vec<T>::len() {
    return m_Size;
}

template<typename T>
T& gallium::Vec<T>::operator[](size_t index) {
    if (index >= m_Size) {
        throw std::runtime_error("Index out of bounds");
    }

    return m_Buffer[index];
}

template<typename T>
gallium::Vec<T>::~Vec() {
    free(m_Buffer);
}

template<typename T>
void gallium::Vec<T>::increase_cap(size_t new_cap) {
    m_Buffer = (T*)realloc(m_Buffer, sizeof(T) * new_cap);
    if (!m_Buffer) {
        throw std::runtime_error("Failed to reallocate memory");
    }

    m_Cap = new_cap;
}

template<typename T>
T* gallium::Vec<T>::allocate(size_t size) {
    T *buffer = (T*)malloc(size);
    if (!buffer) {
        throw std::runtime_error("Failed to allocate memory");
    }

    return buffer;
}
