#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "debug.hpp"

using std::cout;
using std::cerr;
using std::ostream;
using std::string;
using std::ofstream;
using std::stringstream;
using sec = std::chrono::seconds;
using ms = std::chrono::milliseconds;
using us = std::chrono::microseconds;
using sclock = std::chrono::system_clock;
using hclock = std::chrono::high_resolution_clock;

namespace kdebug {

class KDBG {
 public:
  KDBG() = default;
  ~KDBG() { cout << std::endl; }
  static hclock::time_point start_time_;
  static ofstream target_;
};

KDBG storage_;
hclock::time_point KDBG::start_time_ = hclock::now();
ofstream KDBG::target_;

// output color string macro
#define COLOR_STRING(color, s) "\033[" #color ";1m" #s "\033[0m"

string ToTimeString(long t) {
  struct tm* time_val = gmtime(&t);

  stringstream ss;
  ss << time_val->tm_year + 1900 << "/" << time_val->tm_mon + 1 << "/"
     << time_val->tm_mday << "-" << time_val->tm_hour << ":" << time_val->tm_min
     << ":" << time_val->tm_sec;
  return ss.str();
}

ostream& SevereLevel(Severity sev) {
  if (KDBG::target_.is_open()) {
    switch (sev) {
      case info:
      case INFO:
        return KDBG::target_ << "\n[INFO   ";
      case warning:
      case WARNING:
        return KDBG::target_ << "\n[WARNING";
      case error:
      case ERROR:
        return KDBG::target_ << "\n[ERROR  ";
      default:
        return KDBG::target_ << "\n[INFO   ";
    }
  } else {
    switch (sev) {
      case info:
      case INFO:
        return cout << std::endl << "[" << std::setw(8) << COLOR_STRING(32, INFO);
      case warning:
      case WARNING:
        return cout << std::endl
                    << "[" << std::setw(8) << COLOR_STRING(33, WARNING);
      case error:
      case ERROR:
        return cerr << std::endl
                    << "[" << std::setw(8) << COLOR_STRING(31, ERROR);
      default:
        return cout << std::endl << "[" << std::setw(8) << COLOR_STRING(32, INFO);
    }
  }
}

template <>
inline string Unit<sec>() {
  return " sec";
}

template <>
inline string Unit<ms>() {
  return " ms";
}

template <>
inline string Unit<us>() {
  return " us";
}

template <typename Clock, typename Duration>
ostream& KDebug(Severity sev, const string& filename, int line_num,
                bool log_date, bool log_time) {
  // compute time
  auto current = Clock::now();
  auto time_passed = current - KDBG::start_time_;
  long t = std::chrono::duration_cast<Duration>(time_passed).count();
  KDBG::start_time_ = current;
  // prepare output stream
  ostream& os = SevereLevel(sev) << " ";
  // log time
  if (log_date) {
    os << ToTimeString(t);
  } else if (t > 86400000) {
    time_t current_time;
    std::time(&current_time);
    os << ToTimeString(current_time);
  } else if (log_time) {
    os << t << Unit<Duration>();
  }
  os << " " << filename.substr(filename.find_last_of("/") + 1) << ": "
     << line_num << "]: ";
  return os;
}

template ostream& KDebug<sclock, sec>(Severity, const string&, int, bool, bool);
template ostream& KDebug<hclock, ms>(Severity, const string&, int, bool, bool);
template ostream& KDebug<hclock, us>(Severity, const string&, int, bool, bool);

ostream& Log(Severity sev, const string& filename, int line_num) {
  return KDebug<sclock, sec>(sev, filename, line_num, false, true);
}

ostream& Timer(Severity sev, const string& filename, int line_num) {
  return KDebug<hclock, us>(sev, filename, line_num, false, true);
}

ostream& Date(Severity sev, const string& filename, int line_num) {
  return KDebug<sclock, sec>(sev, filename, line_num, true, false);
}

ostream& KDebug(Severity sev, const string& filename, int line_num) {
  return KDebug<hclock, ms>(sev, filename, line_num, true, true);
}

#undef COLOR_STRING

void OutputToFile(const string& program_name) {
  long current_time = sclock::now().time_since_epoch().count();
  string filepath = program_name + ".kdebug." + std::to_string(current_time);
  KDBG::target_.open(filepath);
}

void CloseOutputFile() {
  KDBG::target_.close();
}

} /* end of kdebug namespace */
