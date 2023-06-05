#include "log.h"

/**
 * @brief gets the state of the system
 * @return the state
 */
Log::State Log::get_state () {
    return s;
}

/**
 * @brief gets the file name
 * @return string of the file name
 */
std::string Log::get_filename () {
    return file.filename().string();
}

/**
 * @brief gets the file path
 * @return a string of the file path
 */
std::string Log::get_filepath () {
    return file.string();
}

/**
 * @brief opens a file, sets its state to open, and saves the file path or name,
 *        appending output operations to the end of the file
 * @param f file to be opened
 */
void Log::open_append(const std::string f) {
    close(); // close currently open file
    try {
        fh.open(f, std::ofstream::out | std::ofstream::app ); // try to open file f
        s = Open; // set state to open
        file = f; // save file path/name
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n"; // in the case of io errors
        close();
    }
}

/**
 * @brief opens a file, sets its state to open, and saves the file path or name,
 *        overwriting output operations
 * @param f file to be opened
 */
void Log::open_overwrite(const std::string f) {
    close();
    try {
        fh.open(f, std::ofstream::out );
        s = Open;
        file = f;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        close();
    }
}

/**
 * @brief closes the file, and sets state to be closed
 */
void Log::close () {
    flush(); // flush stream if possible
    if (s == Flushed) { // if flush was successful (or we didn't need to flush)
        fh.close(); // close file
        s = Closed; // set state
    }
}

/**
 * @brief flushes the file, sets state to flush
 */
void Log::flush () {
    if (s == Open) { // if currently open and not flushed
        fh.flush(); // flush
        s = Flushed; // and set state
    }
}

/**
 * @brief Base Constructor, in which the base state is closed and base
 *        file location is ./log.txt
 */
Log::Log() : s(Closed) { // initialize s as closed
    open_append("./log.txt"); // open default file
}

/**
 * @brief Copy constructor sets object state equal to current object's state
 * @param l dereferenced log object
 */
Log::Log(Log &l){
    s = l.s;
}

/**
 * @brief Copy assignment sets object state equal to current object's state
 * @param l dereferenced log object
 */
void Log::operator=(Log &l){
    s = l.s;
}

/**
 * @brief Constructor to open a file other than the default
 * @param f filename
 */
Log::Log(const std::string f) : s(Closed) {
    open_append(f); // open file f
}

/**
 * @brief In the destructor the file handler is closed.
 */
Log::~Log() {
    close();
}

/**
* @brief The overloaded operator will process the incoming string, then return
*        str itself as a reference. This allows chaining of multiple filehandler
*        operations.
* @param str string of incoming data
* @return string str as a reference
*/
Log& Log::operator<<(std::string str) {
    if (s != Closed) fh << str; // only try to push to stream if a file is open
    flush(); // flush after each write
    return *this;
}

/**
 * @brief Overloads the operator to process ints
 * @param i int of incoming data
 * @return int i as a reference
 */
Log& Log::operator<<(int i) {
    if (s != Closed) fh << i;
    flush();
    return *this;
}

/**
 * @brief Overloads the operator to process doubles
 * @param d double of incoming data
 * @return double d as a reference
 */
Log& Log::operator<<(double d) {
    if (s != Closed) fh << d;
    flush();
    return *this;
}
