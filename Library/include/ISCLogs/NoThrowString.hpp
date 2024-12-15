//
// Created by An Inconspicuous Semicolon on 20/06/2024.
//

#pragma once

#include <string>
#include <string_view>

namespace isc::util
{
class NoThrowString
{
public:
    NoThrowString() noexcept;
    NoThrowString(const std::string& string) noexcept;
    NoThrowString(const char* string) noexcept;
    ~NoThrowString() noexcept;

    NoThrowString(const NoThrowString& string) noexcept;
    NoThrowString& operator=(const NoThrowString& string) noexcept;

    NoThrowString(NoThrowString&& string) noexcept;
    NoThrowString& operator=(NoThrowString&& string) noexcept;

    [[nodiscard]] std::string_view get() const noexcept;

private:
    static constexpr const char* s_default_string = "Default String";

    std::string* m_str = nullptr;
};
} // vulren
