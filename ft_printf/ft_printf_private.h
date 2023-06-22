#ifndef CLIB_TEST_FT_PRINTF_PRIVATE_H
#define CLIB_TEST_FT_PRINTF_PRIVATE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define PRINT_BUFFER_SIZE 1024

typedef struct string_data_s {
    char* str;
    size_t str_index;
    size_t max_size;
} string_data_t;

typedef struct buffer_s {
    char buffer[PRINT_BUFFER_SIZE];
    size_t buffer_size;
    bool is_string;
    union {
        int fd;
        string_data_t str_data;
    };
    int ret;
    bool error;
} buffer_t;

// d, i signed / o, u, x, X unsigned
typedef enum length_mod_e {
    NONE = 0,
    HH, // char / unsigned char
    H,  // short / unsigned short
    L,  // long / unsigned long
    LL, // long long / unsigned long long
    J,  // intmax_t / uintmax_t
    T,  // ptrdiff_t / unsigned type of size ptrdiff_t
    Z  // ssize_t / size_t
} length_mod_t;

typedef struct flags_s {
    bool alternate; // '#'
    bool zero;  // '0'
    bool minus; // '-'
    bool space; // ' '
    bool plus;  // '+'
//    bool dec_conversion; // '''
    size_t field_width; // "123..."
    size_t precision; // ".123..."
    length_mod_t length_mod;
} flags_t;

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
} conversion_t;

void flush(buffer_t* buff);
void add_to_buffer(buffer_t* buff, char c);
void print_loop(buffer_t* buffer, const char* restrict* format, va_list ap);
flags_t gather_flags(buffer_t* buffer, const char* restrict* format, va_list ap);

#endif
