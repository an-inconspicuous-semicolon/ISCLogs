# ISCLogs

ISCLogs is a lightweight logging and messaging library designed for runtime issue reporting. It provides robust error classification and logging mechanisms, ranging from debug information to fatal errors.

## Features

- **Message System**: A versatile `Message` class that conveys information about runtime events with various severities.
- **Severity Levels**:
    - Debug
    - Nominal
    - Notice
    - Warning
    - Error
    - Fatal
- **Tracing and Stacktrace**: Add traces to messages to build a stacktrace.
- **Logging**: Configurable `Logger` class that logs messages above a specified severity threshold.
- **Customizable Messages**: Derived message classes (`DebugMessage`, `WarningMessage`, etc.) provide clean, severity-specific message construction.

---

## Classes Overview

### `isc::Message`
The core class representing messages, which include:
- Numerical code
- Name (title)
- Description
- Severity
- Source location (file, line, column, function)

**Main Methods**:
- `message()`: Returns a formatted string with message details.
- `is_failure()`: Checks if the message is an error or higher.
- `add_trace()`: Adds a trace for stacktracing.
- Severity promotion with `promote()`.

### Severity-Based Message Classes
These classes simplify message construction for specific severities:
- `DebugMessage`
- `NominalMessage`
- `NoticeMessage`
- `WarningMessage`
- `ErrorMessage`
- `FatalMessage`

Example:
``` c++
isc::ErrorMessage error(404, "Not Found", "The requested resource was not found.");
```
---

### `isc::Logger`
The `Logger` class filters and logs messages based on a specified severity threshold.

**Main Features**:
- **Threshold Control**: Only messages above the threshold are logged.
- `set_severity()`: Sets the severity threshold dynamically.
- `log_message()`: Logs a message if it meets the threshold.

**Example**:
```c++
class ConsoleLogger : public isc::Logger
{
protected:
    void log_message_internal(const isc::Message& message) const noexcept override
    {
        std::cout << message.message() << std::endl;
    }
};

ConsoleLogger logger(isc::Message::Severity::Warning);
logger.log_message(isc::NoticeMessage(101, "Notice", "This is just info."));
logger.log_message(isc::WarningMessage(201, "Warning", "This is a warning!"));
```
---

## Usage

1. **Creating Messages**:
    ```c++
    isc::ErrorMessage error(500, "Server Error", "Unable to connect to database.");
    if (error.is_failure())
    {
        std::cerr << error.message() << std::endl;
    }
    ```
2. **Using the Logger**:
    ```c++
    ConsoleLogger logger(isc::Message::Severity::Debug);
    logger.log_message(isc::DebugMessage(42, "Debug Log", "Some debug information."));
    ```
3. **Adding Traces**:
    ```c++
    auto fatal = isc::FatalMessage(1, "Fatal Error", "System crash").add_trace("Failed at component X");
    std::cerr << fatal.message() << std::endl;
    ```
    ---

## Requirements
- C++20 (for `std::source_location` and modern language features)

---

## Installation
ISCLogs uses cmake with the `ISCLogs` static library target.

```cmake
add_subdirectory(Libraries/ISCLogs)

target_link_libraries(... ISCLogs)
```
The libraries will now be available under the `ISCLogs` folder

```c++
#include <ISCLogs/ISCLogs.hpp>
```

---

## License
This project is licensed under the **MIT License**.

