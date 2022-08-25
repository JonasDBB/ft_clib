#ifndef FT_CLIB_H
#define FT_CLIB_H

#include <stddef.h>
#include <stdbool.h>

// colors
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

/**
 * log function to use for clear information and easy debugging
 * use "LOG(...)" to use where ... are printf arguments
 * example
 * "LOG("my %s here %d", "log message", 5);"
 * to get an informative log line with message "my log message here 5"
 * @param file filename
 * @param func function name
 * @param line line number
 * @param fmt print fmt
 * @param ... variadic arguments
 */
void log_func(const char* file, const char* func, int line, const char* fmt, ...);
#define LOG(fmt, ...) { \
    log_func(__FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__); \
}

/**
 * get name of errno error
 * @param e errno nr
 * @return errno as string
 */
const char* errno_name(int e);

/**
 * get length of string
 * @param s string
 * @return length of string
 */
size_t ft_strlen(const char* s);

/**
 * set n bytes in memory to the same value
 * @param b pointer to start location
 * @param c value to be set
 * @param len total bytes to be set
 * @return pointer to start
 */
void* ft_memset(void* b, int c, size_t len);

/**
 * set n bytes in memory to 0
 * @param s pointer to start location
 * @param n total bytes to be set
 */
void ft_bzero(void* s, size_t n);

/**
 * find first occurrence of c in s
 * @param s source string
 * @param c character to find
 * @return location of first found occurrence or NULL if not found
 */
char* ft_strchr(const char *s, int c);

/**
 * find last occurrence of c in s
 * @param s source string
 * @param c character to find
 * @return location of last found occurrence or NULL if not found
 */
char* ft_strrchr(const char *s, int c);

/**
 * check if c is a numerical character
 * @param c character to check
 * @return true if c is a numerical character, false otherwise
 */
bool ft_isnum(char c);

/**
 * check if c is an alphabetical or numerical character
 * @param c character to check
 * @return true if c is alphabetical or numerical, false otherwhise
 */
bool ft_isalpha(char c);

/**
 * convert character to lowercase
 * @param c character to convert
 * @return lowercase version of c if c is an uppercase character, unchanged value of c otherwise
 */
char ft_tolower(char c);

/**
 * check if c is a whitespace character
 * @param c character to check
 * @return true if c is a whitespace character, false otherwise
 */
bool ft_isspace(char c);

/**
 * convert a string to long value
 * @param str source string
 * @param endptr if not NULL, will store pointer to first invalid character in str
 * @param base base of the given string, up to 36 (0-9 followed by a-z)
 * base 0 will identify base 10 (no special start), 8 (start with 0) or base 16 (start with 0x)
 * @return converted value or LONG_MAX / LONG_MIN in case of over- / underflow
 */
long ft_strtol(const char *str, char **endptr, int base) __attribute__((nonnull(1)));

#endif
