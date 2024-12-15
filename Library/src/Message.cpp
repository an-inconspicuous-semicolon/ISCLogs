//
// Created by An Inconspicuous Semicolon on 15/12/2024.
//

#include "Message.hpp"

#include <filesystem>
#include <sstream>
#include <utility>

namespace isc
{
inline std::string get_filename(const std::source_location& loc, const std::string& relative_to = "")
{
    // Extract the filename from the path
    const std::filesystem::path file_path = loc.file_name();
    std::string path                      = file_path.filename().string();

    if (relative_to.size() > 0)
    {
        const auto pos = path.find_first_of(relative_to);
        if (pos >= path.size())
            return path;

        path.erase(pos, relative_to.size());
    }

    return path;
}

Message::Message()
= default;

Message::~Message()
= default;

Message::Message(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const Severity severity,
    const std::source_location& location
)
    : m_code(code),
      m_name(std::move(name)),
      m_description(std::move(description)),
      m_severity(severity),
      m_source_location(location),
      m_temp_string(nullptr)
{}

Message::Message(
    const unsigned int code,
    util::NoThrowString name,
    const Severity severity,
    const std::source_location& location
)
    : m_code(code),
      m_name(std::move(name)),
      m_has_description(false),
      m_severity(severity),
      m_source_location(location),
      m_temp_string(nullptr)
{}

char const* Message::what() const
{
    const std::string msg = message();
    m_temp_string         = new(std::nothrow) char[msg.size() + 1];

    strcpy_s(m_temp_string, msg.size() * sizeof(char), msg.c_str());
    return m_temp_string;
}

std::string Message::message() const
{
    std::ostringstream oss;

    std::string severity;

    switch (m_severity)
    {
    case Severity::Debug:
        severity = "[Debug]";
        break;
    case Severity::Nominal:
        severity = "[Nominal]";
        break;
    case Severity::Notice:
        severity = "[Notice]";
        break;
    case Severity::Warning:
        severity = "[Warning]";
        break;
    case Severity::Error:
        severity = "[Error]";
        break;
    case Severity::Fatal:
        severity = "[Fatal]";
        break;
    }

    oss << severity << ": " << m_name.get();
    if (has_description())
        oss << " - " << m_description.get();
    return oss.str();
}

inline bool Message::is_failure() const noexcept
{
    return m_severity >= Severity::Error;
}

inline Message Message::add_trace(const std::string& message) noexcept
{
    m_trace.push_back(message);
    return *this;
}

inline const std::list<std::string>& Message::get_trace() const noexcept
{
    return m_trace;
}

inline unsigned int Message::code() const noexcept
{
    return m_code;
}

inline bool Message::has_description() const noexcept
{
    return m_has_description;
}

inline std::string_view Message::name() const noexcept
{
    return m_name.get();
}

inline std::string_view Message::description() const noexcept
{
    return m_description.get();
}

inline Message::Severity Message::severity() const noexcept
{
    return m_severity;
}

inline unsigned int Message::line() const noexcept
{
    return m_source_location.line();
}

inline unsigned int Message::column() const noexcept
{
    return m_source_location.column();
}

inline std::string_view Message::file() const noexcept
{
    return m_source_location.file_name();
}

inline std::string_view Message::function(const std::string& relative_to) const noexcept
{
    return get_filename(m_source_location, relative_to);
}

inline Message Message::promote(const Severity& severity) noexcept
{
    if (m_severity < severity)
        m_severity = severity;

    return *this;
}

NominalMessage::NominalMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

NominalMessage::NominalMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}

DebugMessage::DebugMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

DebugMessage::DebugMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}

NoticeMessage::NoticeMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

NoticeMessage::NoticeMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}

WarningMessage::WarningMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

WarningMessage::WarningMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}

ErrorMessage::ErrorMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

ErrorMessage::ErrorMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}

FatalMessage::FatalMessage(
    const unsigned int code,
    util::NoThrowString name,
    util::NoThrowString description,
    const std::source_location& location
)
    : Message(code, std::move(name), std::move(description), Severity::Nominal, location)
{}

FatalMessage::FatalMessage(
    const unsigned int code,
    util::NoThrowString name,
    const std::source_location& location
)
    : Message(code, std::move(name), Severity::Nominal, location)
{}
} // isc
