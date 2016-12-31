#ifndef DEBUG_C_H
#define DEBUG_C_H

#ifdef __cplusplus
extern "C" {
#endif

enum KDebugSeverity { KDEBUG_INFO, KDEBUG_WARNING, KDEBUG_ERROR };

void kdebug_log(enum KDebugSeverity sev, const char* filename, int lin_num,
                const char* const message);
void kdebug_timer(enum KDebugSeverity sev, const char* filename, int lin_num,
                  const char* const message);
void kdebug_date(enum KDebugSeverity sev, const char* filename, int lin_num,
                 const char* const message);
void kdebug_kdebug(enum KDebugSeverity sev, const char* filename, int lin_num,
                   const char* const message);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: DEBUG_C_H */
