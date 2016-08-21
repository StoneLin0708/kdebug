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
    dbg();
    ~dbg();

    dbg &set_level(level l);
    void set_fileoutput(const std::string filename);
    template<typename T> dbg& operator<<(T t);
    void log();
    long time();
    static std::string timestr();
    void list();

private:
    typename Clock::time_point _starttime;
    typename Clock::rep _time;

    level _level;
    bool _flag_logged;
    std::stringstream _ss;
    std::ofstream _output_file;
    std::list<std::tuple<typename Clock::rep, level, std::string>> _log;
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

// macros
#ifdef DEBUG_MESSAGE
#define LOG(level) kdebug::debug.set_level(level)
#else
#define LOG(level) kdebug::debug.set_level(kdebug::null)
#endif
