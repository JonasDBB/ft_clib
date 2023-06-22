#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include "ft_clib.h"

static const char* const log_colors[] = {
        [LOG_LVL_DEBUG] = CLR_GRN"DBG",
        [LOG_LVL_WARN] = CLR_YLW"WRN",
        [LOG_LVL_ERROR] = CLR_RED"ERR"
};

log_level current_log_level = LOG_LVL_DEBUG;

void set_log_level(log_level lvl) {
    current_log_level = lvl;
}

void log_func(log_level lvl, const char* file, const char* func, int line, const char* fmt, ...) {
    if (lvl < current_log_level) {
        return;
    }
    char buf[MAX_LOG_SIZE];
    va_list varlist;
    va_start(varlist, fmt);
    vsnprintf(buf, MAX_LOG_SIZE, fmt, varlist);
    va_end(varlist);

    struct timeval t;
    gettimeofday(&t, NULL);
    struct tm* tm = localtime(&t.tv_sec);

    fprintf(stderr, "%s %02d:%02d:%02d.%03d| %s:%d: %s(): [%s]\n" CLR_RESET,
            log_colors[lvl], tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(t.tv_usec / 1000), file, line, func, buf);
}