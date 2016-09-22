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
    file,
    info,
    warning,
    error,
    FILE,
    INFO,
    WARNING,
    ERROR
};


template <typename Clock, typename Duration>
class dbg {
public:
    typedef std::tuple<typename Clock::rep, level, std::string> log_t;
    typedef typename std::list<log_t>::iterator iterator;

    dbg(std::string unit);
    ~dbg();

    dbg &set_level(level l);
    void set_fileoutput(const std::string filename);
    template<typename T> dbg& operator<<(T t) {
        _ss << t;
        switch (_level) {
            case null:
                return *this;
                break;
            case FILE:
            case file:
                if (_output_file.is_open()) {
                    _output_file << t;
                }
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

    std::string time(bool update);
    static std::string current_timestr();
    void log();
    void list();

    iterator begin();
    iterator end();
    log_t back();

private:
    typename Clock::time_point _starttime;
    typename Clock::time_point _lastlogtime;
    typename Clock::rep _time;

    level _level;
    bool _flag_logged, _should_update;
    std::string unit;
    std::stringstream _ss;
    std::ofstream _output_file;
    std::list<log_t> _log;
};

// global variables
typedef dbg<std::chrono::high_resolution_clock,
            std::chrono::microseconds> Timer;
typedef dbg<std::chrono::system_clock,
            std::chrono::milliseconds> Debug;
typedef dbg<std::chrono::system_clock,
            std::chrono::seconds> Log;

extern std::map<level, const std::string> _levelstring;
extern Debug _debug;
extern Timer _timer;
extern Log _log;

}

#undef DBG
#undef TIMER
#undef LOG
#undef SET_FILE
// macros
#ifdef DEBUG_MESSAGE
#define DBG(level) kdebug::_debug.set_level(kdebug::level)
#define TIMER(level) kdebug::_timer.set_level(kdebug::level)
#define LOG(level) kdebug::_log.set_level(kdebug::level)
#define SET_FILE(filename)      \
    kdebug::_debug.set_fileoutput(filename); \
    kdebug::_timer.set_fileoutput(filename); \
    kdebug::_log.set_fileoutput(filename);
#else
#define DBG(level)
#define TIMER(level)
#define LOG(level)
#define SET_FILE(filename)
#endif
