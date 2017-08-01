#ifndef KDEBUG_H
#define KDEBUG_H

// undef old macro
#undef LOG
#undef TIMER
#undef DATE
#undef KDEBUG

#ifdef __cplusplus
// c++ macros
#include "kdebug/debug.hpp"

#ifdef KDEBUG_MESSAGE
#define LOG(level) kdebug::Log(kdebug::level, __FILE__, __LINE__)
#define TIMER(level) kdebug::Timer(kdebug::level, __FILE__, __LINE__)
#define DATE(level) kdebug::Date(kdebug::level, __FILE__, __LINE__)
#define KDEBUG(level) kdebug::KDebug(kdebug::level, __FILE__, __LINE__)
#else
// empty message
#define LOG(level) if (false) std::cout
#define TIMER(level) if (false) std::cout
#define DATE(level) if (false) std::cout
#define KDEBUG(level) if (false) std::cout
#endif

#else
// c macros
#include "debug_c.h"

#ifdef KDEBUG_MESSAGE
#define LOG(level, message) kdebug_log(level, __FILE__, __LINE__, message)
#define TIMER(level, message) kdebug_timer(level, __FILE__, __LINE__, message)
#define DATE(level, message) kdebug_date(level, __FILE__, __LINE__, message)
#define KDEBUG(level, message) kdebug_kdebug(level, __FILE__, __LINE__, message)
#else
// empty message
#define LOG(level, message)
#define TIMER(level, message)
#define DATE(level, message)
#define KDEBUG(level, message)
#endif

#endif /* end of c/c++ macro */
#endif /* end of include guard: KDEBUG_H */
