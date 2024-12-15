//
// Created by An Inconspicuous Semicolon on 20/06/2024.
//

#include "NoThrowString.hpp"

namespace isc::util
{
NoThrowString::NoThrowString() noexcept
= default;

NoThrowString::NoThrowString(const char* string) noexcept
{
    m_str = new(std::nothrow) std::string(string);
}

NoThrowString::NoThrowString(const std::string& string) noexcept
{
    m_str = new(std::nothrow) std::string(string);
}

NoThrowString::~NoThrowString() noexcept
{
    delete m_str;
}

NoThrowString::NoThrowString(const NoThrowString& string) noexcept
{
    if (string.m_str == nullptr)
        m_str = nullptr;
    else
        m_str = new(std::nothrow) std::string(*string.m_str);
}

NoThrowString& NoThrowString::operator=(const NoThrowString& string) noexcept
{
    if (&string == this)
        return *this;

    delete m_str;

    if (string.m_str == nullptr)
        m_str = nullptr;
    else
        m_str = new(std::nothrow) std::string(*string.m_str);

    return *this;
}

NoThrowString::NoThrowString(NoThrowString&& string) noexcept
{
    m_str        = string.m_str;
    string.m_str = nullptr;
}

NoThrowString& NoThrowString::operator=(NoThrowString&& string) noexcept
{
    if (&string == this)
        return *this;

    delete m_str;
    m_str        = string.m_str;
    string.m_str = nullptr;

    return *this;
}

std::string_view NoThrowString::get() const noexcept
{
    if (m_str == nullptr)
        return s_default_string;

    return *m_str;
}
} // vulren
