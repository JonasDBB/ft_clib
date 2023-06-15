#ifndef CLIB_TEST_FT_PRINTF_PRIVATE_H
#define CLIB_TEST_FT_PRINTF_PRIVATE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define PRINT_BUFFER_SIZE 1024

typedef struct buffer_s {
    char buffer[PRINT_BUFFER_SIZE];
    int ret;
    int fd;
    char* str;
    size_t str_index;
    size_t size;
    size_t max_size;
    void (* flusher)(struct buffer_s*);
    bool error;
} buffer_t;

typedef struct flags_s {
    bool alternate; // '#'
    bool zero;  // '0'
    bool minus; // '-'
    bool space; // ' '
    bool plus;  // '+'
//    bool dec_conversion; // '''
    size_t field_width; // "123..."
    size_t precision; // ".123..."
} flags_t;

// d, i signed / o, u, x, X unsigned
typedef struct length_mod_s {
    bool hh; // char / unsigned char
    bool h;  // short / unsigned short
    bool l;  // long / unsigned long
    bool ll; // long long / unsigned long long
    bool j;  // intmax_t / uintmax_t
    bool t;  // ptrdiff_t / unsigned type of size ptrdiff_t
    bool z;  // ssize_t / size_t
} length_mod_t;

typedef enum type_specifier_e {
    DIGIT = 'd',
    DIGIT_ = 'i',
    OCTAL = 'o',
    UNSINGED = 'u',
    HEX = 'x',
    HEX_CAP = 'X',
    CHAR = 'c',
    STRING = 's',
    POINTER = 'p', // same as %#x
    PERCENT = '%'
} conversion_type;

void flush_buffer_fd(buffer_t* buff);
void flush_buffer_str(buffer_t* buff);
void add_to_buffer(buffer_t* buff, char c);
void print_loop(buffer_t* buffer, const char* restrict format, va_list ap);

#endif
