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
#include <ctime>

namespace kdebug{

enum level{
    null,
    file,
    info,
    warning,
    error
};

extern std::map<level,const char*> levelstring;
std::map<level,const char*> levelstring = {
    {null, "null"},
    {file, "file"},
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

extern std::ostream cnull;
class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};
NullBuffer null_buffer;
std::ostream cnull(&null_buffer);

template <typename Clock, typename Duration, const char *const Unit>
class dbg{
public:
    dbg() : flag_logged(true),
            starttime(Clock::now()) {}

    ~dbg() {
        if (output_file.is_open()) output_file.close();
    }

    dbg& set_level(level l)
    {
        if(!flag_logged){
            log();
        }

        _level = l;
        _time = time();
        flag_logged = false;
        return *this;
    }

    void set_fileoutput(const std::string filename) {
        output_file.open(filename.c_str(), std::ios::out);
    }

    template<typename T>
    dbg& operator<<(T t) {
        _ss << t;
        switch (_level) {
            case null:
                cnull << t;
                break;
            case file:
                output_file << "[" << levelstring[_level]
                    << ": " << timestr() << "]: " << t;
                break;
            case info:
            case warning:
                std::cout << "[" << levelstring[_level]
                    << ": " << timestr() << "]: " << t;
                break;
            case error:
                std::cerr << "[" << levelstring[_level]
                    << ": " << timestr() << "]: " << t;
                break;
        }
        return *this;
    }

    void log()
    {
        static std::string s;
        _ss>> s;
        _log.push_back(std::make_tuple(_time, _level, s));
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

    static std::string timestr()
    {
        time_t current_time;
        std::time(&current_time);
        struct tm *time_info = std::localtime(&current_time);
        char buffer[1024];
        std::strftime(buffer, 1024, "%m/%d/%y %A %T", time_info);
        return std::string(buffer);
    }

    void list()
    {
        if(!flag_logged)
            log();
        for(auto i=_log.begin();i!=_log.end();++i)
        {
            std::cout << std::get<0>(*i) << Unit
                << levelstring[std::get<1>(*i)]
                << " : "<< std::get<2>(*i) <<'\n';
        }
    }

    bool flag_logged;


private:
    typename Clock::time_point starttime;

    typename Clock::rep _time;

    level _level;

    std::stringstream _ss;

    std::ofstream output_file;

    std::list<std::tuple<typename Clock::rep, level, std::string>> _log;
};

struct Unit {
    static constexpr char Microseconds[] = " ms";
};

extern dbg<std::chrono::high_resolution_clock,
           std::chrono::microseconds,
           Unit::Microseconds> debug;
dbg<std::chrono::high_resolution_clock,
    std::chrono::microseconds,
    Unit::Microseconds> debug;
}

// macros
#ifdef DEBUG_MESSAGE
#define LOG(level) kdebug::debug.set_level(level)
#else
#define LOG(level) kdebug::debug.set_level(null)
#endif
