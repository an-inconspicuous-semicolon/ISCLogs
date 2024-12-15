//
// Created by An Inconspicuous Semicolon on 02/01/2024.
//

#pragma once

#include <list>
#include <source_location>
#include <stdexcept>
#include <string>

#include "ISCLogs/NoThrowString.hpp"

namespace isc
{
/**
 * @brief The Message class is used to convey information about a problem encountered during runtime.
 */
class Message
        : public std::exception
{
public:
    enum class Severity
    {
        Debug = 0, // Verbose messaging for Debug builds only.
        Nominal,   // Everything is fine, used for reporting that there are no problems or errors, usually has no name or description associated with it.
        Notice,    // General information that can be safely ignored.
        Warning,   // The program detected a potential issue, can usually be ignored.
        Error,     // The program encountered an error, but was/will be able to recover, usually by cutting the line of work.
        Fatal      // The program encountered an unrecoverable error, and must terminate.
    };

public:
    /**
     * Constructs a message object with the default code, name, description, severity, and location.
     */
    Message();
    ~Message() override;

    /**
     * Constructs a message object with the given parameters.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param severity The severity of the message.
     * @param location The location in the code that the error occurred in.
    */
    Message(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        Severity severity,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param severity The severity of the message.
     * @param location The location in the code that the error occurred in.
    */
    Message(
        unsigned int code,
        util::NoThrowString name,
        Severity severity,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Returns the contents of the message
     */
    char const* what() const override;

    /**
     * Returns a string containing the information contained in the message.
     */
    [[nodiscard]] std::string message() const;

    /**
     * Returns whether the message is considered a failure, e.g. its severity is Error or higher.
     */
    [[nodiscard]] inline bool is_failure() const noexcept;

    /**
     * Adds a trace to the message, used to generate a stacktrace of where an error occurred.
     * @param message The message to add at the end of the trace
     * @return The message object for monadic call chains.
     */
    inline Message add_trace(const std::string& message) noexcept;

    /**
     * Returns the stacktrace currently held by the message.
     */
    inline const std::list<std::string>& get_trace() const noexcept;

    /**
     * Returns the numerical code of the message.
     */
    [[nodiscard]] inline unsigned int code() const noexcept;

    /**
     * Returns whether the message has a description.
     */
    [[nodiscard]] inline bool has_description() const noexcept;

    /**
     * Returns the name of the message.
     */
    [[nodiscard]] inline std::string_view name() const noexcept;

    /**
     * Returns the description of the message, or a default description if none was given to the message.
     */
    [[nodiscard]] inline std::string_view description() const noexcept;

    /**
     * Returns the severity of the message.
     */
    [[nodiscard]] inline Severity severity() const noexcept;

    /**
     * Returns the line that the message was generated from.
     */
    [[nodiscard]] inline unsigned int line() const noexcept;

    /**
     * Returns the column that the message was generated from.
     */
    [[nodiscard]] inline unsigned int column() const noexcept;

    /**
     * Returns the file that the message was generated from.
     */
    [[nodiscard]] inline std::string_view file() const noexcept;

    /**
     * Returns the function that the message was generated from.
     */
    [[nodiscard]] inline std::string_view function(const std::string& relative_to = "") const noexcept;

    /**
     * Promotes the severity to _at least_ the given severity. If the message is already that severity or higher, nothing is done.
     * @param severity The severity to promote to.
     * @return The message objet for monadic call chains.
     */
    inline Message promote(const Severity& severity) noexcept;

private:
    unsigned int m_code               = 0;
    util::NoThrowString m_name        = "Default Name";
    bool m_has_description            = true;
    util::NoThrowString m_description = "Default Description";
    Severity m_severity               = Severity::Nominal;
    std::source_location m_source_location;

    std::list<std::string> m_trace;
    mutable char* m_temp_string;
};

class NominalMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of nominal.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    NominalMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of nominal, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    NominalMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};

class DebugMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of debug.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    DebugMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of debug, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    DebugMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};

class NoticeMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of notice.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    NoticeMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of notice, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    NoticeMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};

class WarningMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of warning.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    WarningMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of warning, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    WarningMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};

class ErrorMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of error.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    ErrorMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of error, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    ErrorMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};

class FatalMessage
        : public Message
{
public:
    /**
     * Constructs a message object with the given parameters and a severity of fatal.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param description The description of what happened, usually what is used as the contents of a message box.
     * @param location The location in the code that the error occurred in.
    */
    FatalMessage(
        unsigned int code,
        util::NoThrowString name,
        util::NoThrowString description,
        const std::source_location& location = std::source_location::current()
    );

    /**
     * Constructs a message object with the given parameters and a severity of fatal, but without a description.
     * @param code The numerical code of the message.
     * @param name The name of the message, usually what is used as the title of a message box.
     * @param location The location in the code that the error occurred in.
    */
    FatalMessage(
        unsigned int code,
        util::NoThrowString name,
        const std::source_location& location = std::source_location::current()
    );
};
}
