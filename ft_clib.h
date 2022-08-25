#ifndef FT_PING_FT_CLIB_H
#define FT_PING_FT_CLIB_H

#include <stddef.h>
#include <stdbool.h>

#define CLR_RED "\x1b[31m"
#define CLR_GRN "\x1b[32m"
#define CLR_YLW "\x1b[33m"
#define CLR_BLU "\x1b[34m"
#define CLR_MAG "\x1b[35m"
#define CLR_CYA "\x1b[36m"
#define CLR_RESET "\x1b[0m"

#define MEMSET_TYPE long long
#define MEMSET_TYPE_SIZE sizeof(MEMSET_TYPE)

#define MAX_LOG_SIZE 1024
#define __FILENAME__ (ft_strrchr(__FILE__, '/') ? ft_strrchr(__FILE__, '/') + 1 : __FILE__)

void log_func(const char* file, const char* func, int line, const char* fmt, ...);
#define LOG(fmt, ...) { \
    log_func(__FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__); \
}

const char* errno_name(int e);
size_t ft_strlen(const char* s);
void* ft_memset(void* b, int c, size_t len);
void ft_bzero(void* s, size_t n);
char* ft_strchr(char* s, int c);
char* ft_strrchr(char* s, int c);
bool ft_isnum(char c);
bool ft_isalpha(char c);
char ft_tolower(char c);
bool ft_isspace(char c);
long ft_strtol(const char *str, char **endptr, int base) __attribute__((nonnull(1)));

#endif //FT_PING_FT_CLIB_H
