#include <streambuf>
#include <ctime>

#include "debug.hpp"

using std::map;
using std::ostream;
using std::string;
using std::streambuf;

namespace kdebug{

map<level, const string> levelstring = {
    {null, "null"},
    {file, "file"},
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

map<level, const string> levelunits = {
    {null, ""},
    {file, "file"},
    {info,"info"},
    {warning,"warning"},
    {error,"error"},
};

template <typename Clock, typename Duration>
dbg<Clock, Duration>::dbg()
    : _starttime(Clock::now()), _flag_logged(true) {}

template <typename Clock, typename Duration>
dbg<Clock, Duration>::~dbg() {
    if (_output_file.is_open()) _output_file.close();
}

template <typename Clock, typename Duration>
dbg<Clock, Duration> &dbg<Clock, Duration>::set_level(level l) {
    _level = l;
    _time = time();

    if(!_flag_logged){
        log();
    }
    _flag_logged = false;
    return *this;
}

template <typename Clock, typename Duration>
void dbg<Clock, Duration>::set_fileoutput(const string filename) {
    _output_file.open(filename.c_str(), std::ios::out);
}

template <typename Clock, typename Duration>
template<typename T>
dbg<Clock, Duration> &dbg<Clock, Duration>::operator<< (T t) {
    _ss << t;
    switch (_level) {
        case null:
            return *this;
        case file:
            if (_output_file.is_open()) {
                _output_file << "[" << levelstring[_level]
                    << ": " << timestr() << "]: " << t << '\n';
            }
            break;
        case info:
        case warning:
            std::cout << "[" << levelstring[_level]
                << ": " << timestr() << "]: " << t << '\n';
            break;
        case error:
            std::cerr << "[" << levelstring[_level]
                << ": " << timestr() << "]: " << t << '\n';
            break;
    }
    return *this;
}

template <typename Clock, typename Duration>
void dbg<Clock, Duration>::log() {
    static std::string s;
    _ss>> s;
    _log.push_back(std::make_tuple(_time, _level, s));
    _ss.str(std::string());
    _ss.clear();
    s.clear();
    _flag_logged = true;
}

template <typename Clock, typename Duration>
long dbg<Clock, Duration>::time() {
    return std::chrono::duration_cast
        <std::chrono::microseconds>
        (Clock::now()-_starttime).count();
}


template <typename Clock, typename Duration>
string dbg<Clock, Duration>::timestr() {
    time_t current_time;
    std::time(&current_time);
    struct tm *time_info = std::localtime(&current_time);
    char buffer[1024];
    std::strftime(buffer, 1024, "%m/%d/%y %A %T", time_info);
    return std::string(buffer);
}

template <typename Clock, typename Duration>
void dbg<Clock, Duration>::list() {
    if(!_flag_logged)
        log();

    for(auto i = _log.begin() ; i!= _log.end() ; ++i) {
        std::cout << std::get<0>(*i)
            << levelstring[std::get<1>(*i)]
            << " : "<< std::get<2>(*i) <<'\n';
    }
}

template <typename Clock, typename Duration>
typename dbg<Clock, Duration>::iterator dbg<Clock, Duration>::begin()
{
    return _log.begin();
}

template <typename Clock, typename Duration>
typename dbg<Clock, Duration>::iterator dbg<Clock, Duration>::end()
{
    if(!_flag_logged)
        log();
    return _log.end();
}

template <typename Clock, typename Duration>
typename dbg<Clock, Duration>::log_t& dbg<Clock, Duration>::back()
{
    if(!_flag_logged)
        log();
    return _log.back();
}

template class dbg <std::chrono::high_resolution_clock,
                    std::chrono::microseconds>;

Debug debug;

// implement all type support by ostream
template Debug& Debug::operator<< (bool);
template Debug& Debug::operator<< (short);
template Debug& Debug::operator<< (unsigned short);
template Debug& Debug::operator<< (int);
template Debug& Debug::operator<< (unsigned int);
template Debug& Debug::operator<< (long);
template Debug& Debug::operator<< (unsigned long);
template Debug& Debug::operator<< (float);
template Debug& Debug::operator<< (double);
template Debug& Debug::operator<< (long double);
template Debug& Debug::operator<< (void*);
template Debug& Debug::operator<< (char);
template Debug& Debug::operator<< (const char*);
template Debug& Debug::operator<< (string);
template Debug& Debug::operator<< (streambuf*);
template Debug& Debug::operator<< (ostream& (*fp) (ostream&));
template Debug& Debug::operator<< (std::ios& (*fp)(std::ios&));
template Debug& Debug::operator<< (std::ios_base& (*fp)(std::ios_base&));

}
