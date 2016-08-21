#pragma once
#include <ostream>
#include <sstream>
#include <string>
#include <list>
#include <chrono>
#include <tuple>
#include <map>

namespace kdebug{

enum level{
    info,
    warning,
    error,
};

extern std::map<level,const char*> levelstring;

class dbg{
public:
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::tuple<Clock::rep, level, std::string> log_t;
    typedef std::list<log_t>::iterator iterator;

    const char* levelstr(level);

    std::stringstream& operator<<(level);

    void log();

    iterator begin();
    iterator end();
    log_t& back();

    Clock::rep time();

    void list(level l=error);

    bool flag_logged;

private:
    friend class dbg_construct;
    dbg();
    ~dbg(){};

    Clock::time_point starttime;

    Clock::rep _time;
    level _level;
    std::stringstream _ss;

    std::list<log_t> _log;

};

std::ostream& operator<<(std::ostream&, dbg::log_t&);

extern dbg &debug;

}
