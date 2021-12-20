#include <gallium/String.h>
#include <cstring>

namespace gallium {
    std::ostream& operator<<(std::ostream &os, const gallium::String &s) {
        os<<s.m_Buffer;
        return os;
    }
}

gallium::String::String() {
    m_Size = 0;
    m_Buffer = (char*)malloc(sizeof(char));
    m_Buffer[m_Size] = '\0';
}

gallium::String::String(const char *src) {
    if (src == nullptr) {
        m_Size = 0;
        m_Buffer = (char*)malloc(sizeof(char));
        m_Buffer[m_Size] = '\0';
        return;
    }

    size_t src_size = strlen(src);
    m_Size = src_size;
    m_Buffer = (char*)malloc((m_Size * sizeof(char)) + 1);

    memcpy(m_Buffer, src, m_Size);
    m_Buffer[m_Size] = '\0';
}

gallium::String::String(const String &src) {
    m_Size = src.m_Size;
    m_Buffer = (char*)malloc((m_Size * sizeof(char)) + 1);

    memcpy(m_Buffer, src.m_Buffer, m_Size);
    m_Buffer[m_Size] = '\0';
}

gallium::String::~String() {
    free(m_Buffer);
}

gallium::String& gallium::String::operator=(const char *src) {
    set_buffer(src);
    return *this;
}

gallium::String& gallium::String::operator=(const String &rhs) {
    if (&rhs != this) {
        set_buffer(rhs.m_Buffer);
    }

    return *this;
}

void gallium::String::extend(const char *rhs) {
    size_t prev_size = m_Size;
    m_Size += strlen(rhs);
    m_Buffer = (char*)realloc(m_Buffer, (m_Size * sizeof(char)) + 1);

    for(size_t buf_start = prev_size, rhs_start = 0; buf_start < m_Size; buf_start++, rhs_start++) {
        m_Buffer[buf_start] = rhs[rhs_start];
    }

    m_Buffer[m_Size] = '\0';
}

void gallium::String::extend(const String &rhs) {
    extend(rhs.m_Buffer);
}

gallium::String gallium::String::operator+(const char *rhs) {
    String s = m_Buffer;
    s.extend(rhs);

    return s;
}

gallium::String gallium::String::operator+(const String &rhs) {
    String s = m_Buffer;
    s.extend(rhs);

    return s;
}

gallium::String& gallium::String::operator+=(const char *rhs) {
    extend(rhs);

    return *this;
}

gallium::String& gallium::String::operator+=(const String &rhs) {
    extend(rhs);

    return *this;
}

char gallium::String::pop() {
    char last = m_Buffer[m_Size - 1];

    m_Size -= 1;
    m_Buffer = (char*)realloc(m_Buffer, (m_Size * sizeof(m_Size)) + 1);

    return last;
}

gallium::String::operator const char *() {
    return m_Buffer;
}

void gallium::String::set_buffer(const char *rhs) {
    free(m_Buffer);
    m_Size = strlen(rhs);
    m_Buffer = (char *) malloc((m_Size * sizeof(char)) + 1);

    memcpy(m_Buffer, rhs, m_Size);
    m_Buffer[m_Size] = '\0';
}
