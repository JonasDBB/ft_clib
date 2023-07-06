#include "ft_clib.h"
#include "ft_printf_private.h"
#include <stdint.h>
#include <unistd.h>

static long long get_signed_digit_arg(flags_t flags, va_list ap) {
    switch (flags.length_mod) {
        case NONE:
            return va_arg(ap, int);
        case HH:
            return (char)va_arg(ap, int);
        case H:
            return (short)va_arg(ap, int);
        case L:
            return va_arg(ap, long);
        case LL:
            return va_arg(ap, long long);
        case J:
            return va_arg(ap, intmax_t);
        case T:
            return va_arg(ap, ptrdiff_t);
        case Z:
            return va_arg(ap, ssize_t);
    }
}

static long long get_unsigned_digit_arg(flags_t flags, va_list ap) {
    switch (flags.length_mod) {
        case NONE:
            return va_arg(ap, unsigned int);
        case HH:
            return (unsigned char)va_arg(ap, unsigned int);
        case H:
            return (unsigned short)va_arg(ap, unsigned int);
        case L:
            return va_arg(ap, unsigned long);
        case LL:
            return va_arg(ap, unsigned long long);
        case J:
            return va_arg(ap, uintmax_t);
        case T:
            return va_arg(ap, ptrdiff_t);
        case Z:
            return va_arg(ap, size_t);
    }
}

void digit(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;

    char digit_string[20];
    long long n = get_signed_digit_arg(flags, ap);
    ft_lltoa_base(n, (char*)digit_string, 10);
}

void octal(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;

    char digit_string[20];
    long long n = get_signed_digit_arg(flags, ap);
    ft_lltoa_base(n, (char*)digit_string, 8);
}

void unsigned_int(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;

    char digit_string[20];
    long long n = get_unsigned_digit_arg(flags, ap);
    ft_lltoa_base(n, (char*)digit_string, 10);
}

static void hex(buffer_t* buffer, flags_t flags, va_list ap, bool is_upper) {
    UNUSED buffer;

    char digit_string[20];
    long long n = get_unsigned_digit_arg(flags, ap);
    ft_lltoa_base(n, (char*)digit_string, 16);
    if (is_upper) {
        for (size_t i = 0; i < 20 && digit_string[i] != 0; ++i) {
            digit_string[i] = ft_toupper(digit_string[i]);
        }
    }
}

void hex_lower(buffer_t* buffer, flags_t flags, va_list ap) {
    hex(buffer, flags, ap, false);
}

void hex_upper(buffer_t* buffer, flags_t flags, va_list ap) {
    hex(buffer, flags, ap, true);
}

void character(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED flags;
    unsigned char chr = (unsigned char)va_arg(ap, int);
    add_to_buffer(buffer, (char)chr);
}

void string(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void pointer(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void percent(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED flags;
    UNUSED ap;
    add_to_buffer(buffer, '%');
}
