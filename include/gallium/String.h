//
// Created by mdgaziur001 on 11/18/21.
//
#pragma once
#include <malloc.h>
#include <ostream>

namespace gallium {
    class String {
    public:
        // Constructors
        String(const char*);
        String(const String&);
        String();
        ~String();

        void    extend(const String&);
        void    extend(const char*);
        char    pop();
        size_t  len();

        // Operator overloads
        friend   std::ostream& operator<<(std::ostream&, const String&);
        String&  operator=(const char*);
        String&  operator=(const String&);
        String   operator+(const char*);
        String   operator+(const String&);
        String&  operator+=(const char*);
        String&  operator+=(const String&);
        char     operator[](size_t idx) const;

        // type cast
        explicit operator const char*();

    private:
        char   *m_Buffer = nullptr;
        size_t  m_Size = 0;

        void set_buffer(const char*);
    };
}