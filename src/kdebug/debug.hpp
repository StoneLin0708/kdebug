#pragma once
#include <sstream>
#include <string>
#include <list>
#include <chrono>
#include <tuple>
#include <map>
#include <iostream>
#include <fstream>


namespace kdebug {

enum level {
    null,
    info,
    warning,
    error,
    INFO,
    WARNING,
    ERROR
};

void file_logging_on();
void file_logging_off();
void file_name_on();
void file_name_off();

template <typename Clock, typename Duration>
class dbg {
public:
    dbg(std::string unit);
    ~dbg();

    template<typename T> dbg &operator<<(T t) {
        switch (_level) {
            case null:
                return *this;
                break;
            case INFO:
            case info:
            case WARNING:
            case warning:
                std::cout << t;
                break;
            case ERROR:
            case error:
                std::cerr << t;
                break;
        }
        return *this;
    }
    dbg &output(level l, const std::string &file_name, int line_number);

private:
    typename Clock::time_point _starttime;

    std::string get_current_date_string();
    std::string get_level_string(level l);
    std::string get_current_time_string(bool update);
    void set_fileoutput(const std::string filename);
    static std::string current_timestr();

    level _level;
    bool _flag_logged, _should_update, _file_output;
    std::string _unit;
    std::ofstream _output_file;
};

// global variables
typedef dbg<std::chrono::high_resolution_clock,
            std::chrono::microseconds> Timer;
typedef dbg<std::chrono::system_clock,
            std::chrono::milliseconds> Debug;
typedef dbg<std::chrono::system_clock,
            std::chrono::seconds> Log;

extern time_t _current_console_time, _current_file_time;
extern Debug _debug;
extern Timer _timer;
extern Log _log;

}

#undef DBG
#undef TIMER
#undef LOG
// macros
#ifdef DEBUG_MESSAGE
#define DBG(level)    \
    kdebug::_debug.output(kdebug::level, __FILE__, __LINE__)
#define TIMER(level)  \
    kdebug::_timer.output(kdebug::level, __FILE__, __LINE__)
#define LOG(level)    \
    kdebug::_log.output(kdebug::level, __FILE__, __LINE__)
#else
#define DBG(level)
#define TIMER(level)
#define LOG(level)
#endif
