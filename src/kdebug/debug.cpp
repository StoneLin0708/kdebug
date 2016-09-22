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

const string s_esc(1,(char)27);

//how can i do this in compile time
string strcolor(string &&s,string &&color){
    return s_esc+"["+color+";1m"+s+s_esc+"[0m";
}

namespace kdebug{

template <typename Clock, typename Duration>
dbg<Clock, Duration>::dbg(std::string unit)
    : _starttime(Clock::now()), _flag_logged(true),
      _current_console_time(0), _current_file_time(0), _unit(unit) {}

template <typename Clock, typename Duration>
dbg<Clock, Duration>::~dbg() {
    if (_output_file.is_open()) _output_file.close();
}

template <typename Clock, typename Duration>
dbg<Clock, Duration> &dbg<Clock, Duration>::output(level l,
                                                   const string &file_name,
                                                   int line_number) {
    // 1. write the date time if changes
    // 2. write the logging level
    // 3. write timing
    // 4. write filename and line number

    bool update_time = false;
    update_time = (l == info || l == warning || l == error);

    stringbuf buf;
    ostream out(&buf);
    out << std::flush << get_current_date_string() << std::flush
        << '[' << get_level_string(l) << " | "
        << get_current_time_string(update_time) << " | "
        << file_name.substr(file_name.find_last_of("/")+1)
        << ":" << line_number << "] ";

    switch (_level) {
        case null:
            return *this;
        case INFO:
        case info:
        case WARNING:
        case warning:
            cout << std::endl << buf.str();
            break;
        case ERROR:
        case error:
            cerr << std::endl << buf.str();
            break;
    }
    return *this;
}

template <typename Clock, typename Duration>
string dbg<Clock, Duration>::get_current_date_string() {
    stringbuf buf;
    ostream out(&buf);

    auto now = Clock::now();
    time_t current_time = Clock::to_time_t(now);
    struct tm *time_info = std::localtime(&current_time);
    char buffer[1024] = {'\0'};
    std::strftime(buffer, 1024, "[%m/%d/%y %A]\n", time_info);

    if (_file_output) {
        if (current_time - _current_file_time > 86400) {
            _current_file_time = current_time;
            out << buffer;
        }
    } else {
        if (current_time - _current_console_time > 86400) {
            _current_console_time = current_time;
            out << buffer;
        }
    }
    return buf.str();
}

template <typename Clock, typename Duration>
string dbg<Clock, Duration>::get_level_string(level l) {
    _level = l;

    map<level, const string> levelstring = {
        {null,    "null    "},
        {info,    strcolor("info    ","32")},
        {warning, strcolor("warning ","33")},
        {error,   strcolor("error   ","31")},
        {INFO,    strcolor("info    ","32")},
        {WARNING, strcolor("warning ","33")},
        {ERROR,   strcolor("error   ","31")},
    };

    stringbuf buf;
    ostream out(&buf);
    out << levelstring[_level];
    return buf.str();
}

template <typename Clock, typename Duration>
void dbg<Clock, Duration>::set_fileoutput(const string filename) {
    if (_output_file.is_open()) {
        _output_file.close();
    }
    _output_file.open(filename.c_str(), std::ios::out);
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
string dbg<Clock, Duration>::get_current_time_string(bool update) {
    const long timepassed = std::chrono::duration_cast<Duration>
        (Clock::now()-_starttime).count();

    if (update) _starttime = Clock::now();

    stringstream ss;
    ss << timepassed << _unit;
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

    // for(auto i = _log.begin() ; i!= _log.end() ; ++i) {
    //     std::cout << std::get<0>(*i)
    //         << _levelstring[std::get<1>(*i)]
    //         << " : "<< std::get<2>(*i) <<'\n';
    // }
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

Debug _debug(" ms");
Timer _timer(" us");
Log _log(" sec");

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
