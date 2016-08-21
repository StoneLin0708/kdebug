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

    dbg();
    ~dbg();

    dbg &set_level(level l);
    void set_fileoutput(const std::string filename);
    template<typename T> dbg& operator<<(T t);
    void log();
    long time();
    static std::string timestr();
    void list();

    iterator begin();
    iterator end();
    log_t& back();

private:
    typename Clock::time_point _starttime;
    typename Clock::rep _time;

    level _level;
    bool _flag_logged;
    std::stringstream _ss;
    std::ofstream _output_file;
    std::list<log_t> _log;
};

// global variables
typedef dbg<std::chrono::high_resolution_clock,
            std::chrono::microseconds> Debug;
// typedef dbg<std::chrono::system_clock,
//             std::chrono::seconds> Debug;
extern std::map<level, const std::string> levelstring;
extern std::ostream cnull;
extern Debug debug;


}

template <typename Clock, typename Duration>
std::ostream& operator<<(std::ostream& os, typename kdebug::dbg<Clock,Duration>::log_t& l)
{
    os<< std::get<0>(l)<< ' '
      << kdebug::levelstring[std::get<1>(l)]<<" : "
      << std::get<2>(l);
    return os;
}

// macros
#ifdef DEBUG_MESSAGE
#define LOG(level) kdebug::debug.set_level(level)
#else
#define LOG(level) kdebug::debug.set_level(kdebug::null)
#endif
