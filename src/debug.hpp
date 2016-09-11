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
    error
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
    template<typename T> dbg& operator<<(T t);
    std::string time();
    static std::string current_timestr();
    void log();
    void list();

    iterator begin();
    iterator end();
    log_t back();

private:
    typename Clock::time_point _starttime;
    typename Clock::rep _time;

    level _level;
    bool _flag_logged;
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

extern std::map<level, const std::string> levelstring;
extern Debug debug;
extern Timer timer;
extern Log log;

}

std::ostream& operator<<(std::ostream& os,
                         kdebug::Debug::log_t& l);

#undef DBG
#undef TIMER
#undef LOG
// macros
#ifdef DEBUG_MESSAGE
#define DBG(level) kdebug::debug.set_level(kdebug::level)
#define TIMER(level) kdebug::timer.set_level(kdebug::level)
#define LOG(level) kdebug::log.set_level(kdebug::level)
#else
#define DBG(level) kdebug::debug.set_level(kdebug::null)
#define TIMER(level) kdebug::timer.set_level(kdebug::null)
#define LOG(level) kdebug::log.set_level(kdebug::null)
#endif

