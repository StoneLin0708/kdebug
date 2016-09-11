#include <streambuf>
#include <ctime>
#include <iomanip>

#include "debug.hpp"

using std::cout;
using std::cerr;
using std::map;
using std::ostream;
using std::string;
using std::streambuf;
using std::stringbuf;
using std::stringstream;

namespace kdebug{

map<level, const string> levelstring = {
    {null,    "null:    "},
    {file,    "file:    "},
    {info,    "info:    "},
    {warning, "warning: "},
    {error,   "error:   "},
};

template <typename Clock, typename Duration>
dbg<Clock, Duration>::dbg(std::string unit)
    : _starttime(Clock::now()), _flag_logged(true), unit(unit) {}

template <typename Clock, typename Duration>
dbg<Clock, Duration>::~dbg() {
    if (_output_file.is_open()) _output_file.close();
}

template <typename Clock, typename Duration>
dbg<Clock, Duration> &dbg<Clock, Duration>::set_level(level l) {
    _level = l;
    stringbuf buf;
    ostream output(&buf);
    output << "[" << levelstring[_level]
        << current_timestr()
        << " | " << time() << unit << "]: ";

    switch (_level) {
        case null:
            return *this;
        case file:
            if (_output_file.is_open()) {
                _output_file << std::endl << buf.str();
            }
            break;
        case info:
        case warning:
            cout << std::endl << buf.str();
            break;
        case error:
            cerr << std::endl << buf.str();
            break;
    }
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
            break;
        case file:
            if (_output_file.is_open()) {
                _output_file << t;
            }
            break;
        case info:
            break;
        case warning:
            cout << t;
            break;
        case error:
            cerr << t;
            break;
    }
    return *this;
}

template <typename Clock, typename Duration>
void dbg<Clock, Duration>::log() {
    string s;
    _ss >> s;

    _log.push_back(std::make_tuple(_time, _level, s));
    _ss.str(string());
    _ss.clear();
    s.clear();
    _flag_logged = true;
}

template <typename Clock, typename Duration>
string dbg<Clock, Duration>::time() {
    const long timepassed = std::chrono::duration_cast<Duration>
        (Clock::now()-_starttime).count();
    _starttime = Clock::now();

    stringstream ss;
    ss << timepassed;
    return ss.str();
}


template <typename Clock, typename Duration>
string dbg<Clock, Duration>::current_timestr() {
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
typename dbg<Clock, Duration>::iterator dbg<Clock, Duration>::begin() {
    return _log.begin();
}

template <typename Clock, typename Duration>
typename dbg<Clock, Duration>::iterator dbg<Clock, Duration>::end() {
    if(!_flag_logged)
        log();
    return _log.end();
}

template <typename Clock, typename Duration>
typename dbg<Clock, Duration>::log_t dbg<Clock, Duration>::back() {
    if(!_flag_logged)
        log();
    if (_log.size() > 0) {
        return _log.back();
    } else {
        string empt = "empty";
        return std::make_tuple(_time, null, empt);
    }
}

template class dbg <std::chrono::high_resolution_clock,
                    std::chrono::microseconds>;
template class dbg <std::chrono::system_clock,
                    std::chrono::seconds>;
template class dbg <std::chrono::system_clock,
                    std::chrono::milliseconds>;

Debug debug(" ms");
Timer timer(" us");
Log log(" sec");

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

template Timer& Timer::operator<< (bool);
template Timer& Timer::operator<< (short);
template Timer& Timer::operator<< (unsigned short);
template Timer& Timer::operator<< (int);
template Timer& Timer::operator<< (unsigned int);
template Timer& Timer::operator<< (long);
template Timer& Timer::operator<< (unsigned long);
template Timer& Timer::operator<< (float);
template Timer& Timer::operator<< (double);
template Timer& Timer::operator<< (long double);
template Timer& Timer::operator<< (void*);
template Timer& Timer::operator<< (char);
template Timer& Timer::operator<< (const char*);
template Timer& Timer::operator<< (string);
template Timer& Timer::operator<< (streambuf*);
template Timer& Timer::operator<< (ostream& (*fp) (ostream&));
template Timer& Timer::operator<< (std::ios& (*fp)(std::ios&));
template Timer& Timer::operator<< (std::ios_base& (*fp)(std::ios_base&));

template Log& Log::operator<< (bool);
template Log& Log::operator<< (short);
template Log& Log::operator<< (unsigned short);
template Log& Log::operator<< (int);
template Log& Log::operator<< (unsigned int);
template Log& Log::operator<< (long);
template Log& Log::operator<< (unsigned long);
template Log& Log::operator<< (float);
template Log& Log::operator<< (double);
template Log& Log::operator<< (long double);
template Log& Log::operator<< (void*);
template Log& Log::operator<< (char);
template Log& Log::operator<< (const char*);
template Log& Log::operator<< (string);
template Log& Log::operator<< (streambuf*);
template Log& Log::operator<< (ostream& (*fp) (ostream&));
template Log& Log::operator<< (std::ios& (*fp)(std::ios&));
template Log& Log::operator<< (std::ios_base& (*fp)(std::ios_base&));

}
/*
std::ostream& operator<<(std::ostream& os, kdebug::Debug::log_t& l) {
    os<< std::get<0>(l)<< ' '
      << kdebug::levelstring[std::get<1>(l)]<<" : "
      << std::get<2>(l);
    return os;
}

std::ostream& operator<<(std::ostream& os, kdebug::Timer::log_t& l) {
    os<< std::get<0>(l)<< ' '
      << kdebug::levelstring[std::get<1>(l)]<<" : "
      << std::get<2>(l);
    return os;
}

std::ostream& operator<<(std::ostream& os, kdebug::Log::log_t& l) {
    os<< std::get<0>(l)<< ' '
      << kdebug::levelstring[std::get<1>(l)]<<" : "
      << std::get<2>(l);
    return os;
}
*/
