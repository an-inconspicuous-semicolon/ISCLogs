//
// Created by An Inconspicuous Semicolon on 15/12/2024.
//

#include "Logger.hpp"

namespace isc
{
constexpr Logger::Logger(const Message::Severity threshold) noexcept
    : m_threshold(threshold)
{}

inline void Logger::log_message(const Message& message) const noexcept
{
    if (message.severity() >= m_threshold)
        log_message_internal(message);
}

void Logger::set_severity(const Message::Severity& severity) noexcept
{
    m_threshold = severity;
}
} // isc
