#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>

namespace kdebug {

enum Severity { info, INFO, warning, WARNING, error, ERROR };

// convert time to string representation
std::string ToTimeString(long t);
// output to different severity stream
std::ostream& SevereLevel(Severity severity);
// units for different duration
template <typename Duration>
inline std::string Unit();
// logging
template <typename Clock, typename Duration>
inline std::ostream& KDebug(Severity sev, const std::string& filename,
                            int line_num, bool log_date, bool log_time);
// function call to wrap c++11
std::ostream& Log(Severity sev, const std::string& filename, int line_num);
std::ostream& Timer(Severity sev, const std::string& filename, int line_num);
std::ostream& Date(Severity sev, const std::string& filename, int line_num);
std::ostream& KDebug(Severity sev, const std::string& filename, int line_num);
void OutputToFile(const std::string& program_name);
void CloseOutputFile();
}

#endif /* end of include guard: DEBUG_HPP */
