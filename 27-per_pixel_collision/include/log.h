#ifdef USE_LOG_DEBUG
#include <stdio.h>
void LOG_debug(const char *fmt, ...);
#define LOG_DEBUG(msg) printf("\x1b[32mDEBUG\x1b[m "\
		"\x1b[33m%s\x1b[m:\x1b[34m%d\x1b[m: ",\
		__FILE__, __LINE__); LOG_debug msg
#else
#define LOG_DEBUG(msg)
#endif

#ifdef USE_LOG_ERROR
#include <stdio.h>
void LOG_error(const char *fmt, ...);
#define LOG_ERROR(msg) fprintf(stderr, "\x1b[31mERROR\x1b[m "\
		"\x1b[33m%s\x1b[m:\x1b[34m%d\x1b[m: ",\
		__FILE__, __LINE__); LOG_error msg
#else
#define LOG_ERROR(msg)
#endif
