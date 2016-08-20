#pragma once
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

    const char* levelstr(level);

    std::stringstream& operator<<(level);

    void log();

    auto time();

    void list();

    bool flag_logged;

private:
    friend class dbg_construct;
    dbg();
    ~dbg(){};

    Clock::time_point starttime;

    Clock::rep _time;
    level _level;
    std::stringstream _ss;

    std::list<std::tuple<Clock::rep, level, std::string>> _log;

};

extern dbg &debug;

}
