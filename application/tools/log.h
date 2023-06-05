#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

#include "macro.h"

/// Logging file for sending output to a file
class Log
{

public:
    /// @brief Enum representing the logger's state
    enum State {
        Open = 'o',
        Closed = 'c',
        Flushed = 'f',
    };

    /// @brief Base Constructor
    Log();

    /// @brief Copy Contructor
    Log(Log &);

    /// @brief Copy assignment
    void operator=(Log &);

    /// @brief Current state of the logger
    State get_state ();

    /// @brief Currently open file's name
    std::string get_filename ();

    /// @brief Currently open file's path
    std::string get_filepath ();

    /// @brief Open file, appending new content to EOF
    void open_append (const std::string f);

    /// @brief Open file, erasing existing content
    void open_overwrite (const std::string f);

    /// @brief Close file
    void close ();

    /// @brief Flush stream
    void flush ();

    /// @brief Constructor taking a std::string for a file to open
    Log(const std::string f);

    ~Log();

    /// @brief Overloads operator<< for strings
    Log& operator<<(const std::string str);

    /// @brief Overloads operator<< for ints
    Log& operator<<(const int i);

    /// @brief Overloads operator<< for doubles
    Log& operator<<(const double d);
private:

    std::ofstream fh; // The file handler.
    std::filesystem::path file; // current file
    State s; // state
};

#endif // LOG_H
