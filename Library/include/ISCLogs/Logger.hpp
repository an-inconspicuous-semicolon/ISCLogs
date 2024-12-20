//
// Created by An Inconspicuous Semicolon on 15/12/2024.
//

#pragma once
#include "Message.hpp"

namespace isc
{
/**
 * Base class for a logger capable of logging messages above a certain severity threshold.
 */
class Logger
{
public:
    /**
     * Constructs the logger with the default threshold of nominal.
     */
    constexpr Logger() noexcept = default;
    /**
     * Constructs the logger with the specified threshold.
     * @param threshold The threshold above which a message will be logged.
     */
    constexpr Logger(Message::Severity threshold) noexcept;
    virtual ~Logger() noexcept = default;

    /**
     * Logs a message if it is above the logger's threshold.
     * @param message The message to log.
     */
    void log_message(const Message& message) const noexcept;

    /**
     * Sets the severity threshold that the logger will use.
     * @param severity The severity above which a message will be logged.
     */
    void set_severity(const Message::Severity& severity) noexcept;
protected:
    /**
     * Actually logs a message.
     * @param message The message to log.
     */
    virtual void log_message_internal(const Message& message) const noexcept = 0;

private:
    Message::Severity m_threshold = Message::Severity::Nominal;
};
} // isc
