#ifdef USE_LOG_DEBUG
#include <stdarg.h>
#include <stdio.h>
#include "../include/log.h"
void LOG_debug(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}
#endif

#ifdef USE_LOG_ERROR
#include <stdarg.h>
#include <stdio.h>
#include "../include/log.h"
void LOG_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}
#endif
