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

    dbg()
    {
        starttime = Clock::now();
        flag_logged = true;
    }

    void set_level(level l)
    {
        if(!flag_logged){
            log();
        }

        _level = l;
        _time = time();
        flag_logged = false;
    }

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

    void log()
    {
        static std::string s;
        _ss>> s;
        _log.push_back(make_tuple(_time, _level, s));
        _ss.str(std::string());
        _ss.clear();
        s.clear();
        flag_logged = true;
    }

    long time()
    {
        return std::chrono::duration_cast
            <std::chrono::microseconds>
            (Clock::now()-starttime).count();
    }

    static std::string timestr();

    void list()
    {
        if(!flag_logged)
            log();
        for(auto i=_log.begin();i!=_log.end();++i)
        {
            std::cout << std::get<0>(*i) << " "
                << levelstring[std::get<1>(*i)]
                << " : "<< std::get<2>(*i) <<'\n';
        }
    }

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

std::map<level,const char*> levelstring = {
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};

NullBuffer null_buffer;
std::ostream cnull(&null_buffer);
dbg debug;

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
