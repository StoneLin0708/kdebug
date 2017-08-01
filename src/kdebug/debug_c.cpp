#include "kdebug/debug.hpp"
#include "kdebug/debug_c.h"

kdebug::Severity Map(KDebugSeverity sev) {
  switch (sev) {
    case KDEBUG_INFO:
      return kdebug::Severity::INFO;
    case KDEBUG_WARNING:
      return kdebug::Severity::WARNING;
    case KDEBUG_ERROR:
      return kdebug::Severity::ERROR;
    default:
      return kdebug::Severity::INFO;
  }
  return kdebug::Severity::INFO;
}

void kdebug_log(KDebugSeverity sev, const char* const filename, int line_num,
                const char* const message) {
  kdebug::Log(Map(sev), filename, line_num) << message;
}

void kdebug_timer(KDebugSeverity sev, const char* const filename, int line_num,
                const char* const message) {
  kdebug::Timer(Map(sev), filename, line_num) << message;
}

void kdebug_date(KDebugSeverity sev, const char* const filename, int line_num,
                const char* const message) {
  kdebug::Date(Map(sev), filename, line_num) << message;
}

void kdebug_kdebug(KDebugSeverity sev, const char* const filename, int line_num,
                const char* const message) {
  kdebug::KDebug(Map(sev), filename, line_num) << message;
}
