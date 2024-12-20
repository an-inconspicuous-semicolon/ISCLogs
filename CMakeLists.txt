cmake_minimum_required(VERSION 3.5)

project(ISCLogs
        VERSION 1.0.1
        DESCRIPTION "A c++20 Logging Library"
        HOMEPAGE_URL "https://github.com/an-inconspicuous-semicolon/ISCLogs"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

add_library(ISCLogs STATIC
        Library/include/ISCLogs/ISCLogs.hpp
        Library/include/ISCLogs/Logger.hpp
        Library/src/Logger.cpp
        Library/include/ISCLogs/Message.hpp
        Library/src/Message.cpp
        Library/include/ISCLogs/NoThrowString.hpp
        Library/src/NoThrowString.cpp
)

target_include_directories(ISCLogs PUBLIC Library/include PRIVATE Library/include/ISCLogs)
