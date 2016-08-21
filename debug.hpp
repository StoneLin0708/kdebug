#pragma once
#include <sstream>
#include <string>
#include <list>
#include <chrono>
#include <tuple>
#include <map>
#include <iostream>
#include <streambuf>
#include <fstream>

namespace kdebug{

enum level{
    null,
    file,
    info,
    warning,
    error
};

extern std::map<level,const char*> levelstring;
extern std::ostream cnull;

class dbg{
public:
    typedef std::chrono::high_resolution_clock Clock;

    dbg();

    void set_level(level l);

    template<typename T>
    dbg& operator<<(T t) {
        _ss << t;
        switch (_level) {
          case null:
            cnull << t;
            break;
          case file:
          case info:
          case warning:
            std::cout << t;
            break;
          case error:
            std::cerr << t;
            break;
        }
        return *this;
    }

    void log();

    long time();

    void list();

    bool flag_logged;


private:

    Clock::time_point starttime;

    Clock::rep _time;

    level _level;

    std::stringstream _ss;

    std::ofstream output_file;

    std::list<std::tuple<Clock::rep, level, std::string>> _log;
};

extern dbg debug;

#ifdef DEBUG_MESSAGE
#define LOG(level)           \
    debug.set_level(level);  \
    debug
#else
#define LOG(level)           \
    debug.set_level(null);  \
    debug
#endif

}
