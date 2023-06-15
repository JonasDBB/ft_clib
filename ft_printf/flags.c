#include "ft_clib.h"
#include "ft_printf_private.h"


const char* const mod_flags = "#0- +";

static bool is_mod_flag(char c) {
    for (size_t i = 0; i < ft_strlen(mod_flags); ++i) {
        if (c == mod_flags[i]) {
            return true;
        }
    }
    return false;
}

static void set_mod_flag(flags_t* flags, char c) {
    switch (c) {
        case '#':
            flags->alternate = true;
            break;
        case '0':
            flags->zero = true;
            break;
        case '-':
            flags->minus = true;
            break;
        case ' ':
            flags->space = true;
            break;
        case '+':
            flags->plus = true;
            break;
        default:
            break;
    }
}

static void set_mod_flags(buffer_t* buffer, const char* restrict format, flags_t* flags) {
    while (*format && is_mod_flag(*format)) {
        set_mod_flag(flags, *format);
        ++format;
    }
    if (*format == 0) {
        buffer->error = true;
    }
};

static void set_width(buffer_t* buffer, const char* restrict format, va_list ap, flags_t* flags) {
    if (*format == '*') {
        int width_arg = va_arg(ap, int);
        if (width_arg < 0) {
            flags->minus = true;
            flags->field_width = -width_arg;
        }
        ++format;
    } else if (ft_isnum(*format)) {
        char* inc;
        flags->field_width = ft_strtol(format, &inc, 10);
        format = inc;
    }
    if (*format == 0) {
        buffer->error = true;
    }
}

static void set_precision(buffer_t* buffer, const char* restrict format, va_list ap, flags_t* flags) {
    if (*format != '.') {
        return;
    }
    ++format;
    if (*format == '*') {
        int precision_arg = va_arg(ap, int);
        if (precision_arg > 0) {
            flags->precision = precision_arg;
        }
        ++format;
    } else if (ft_isnum(*format)) {
        char* inc;
        flags->precision = ft_strtol(format, &inc, 10);
        format = inc;
    }
    if (*format == 0) {
        buffer->error = true;
    }
}

static void set_length_mod(buffer_t* buffer, const char* restrict format, flags_t* flags) {
    switch (*format) {
        case 'l': {
            flags->length_mod = L;
            ++format;
            if (*format == 'l') {
                flags->length_mod = LL;
                ++format;
            }
            break;
        }
        case 'h': {
            flags->length_mod = H;
            ++format;
            if (*format == 'h') {
                flags->length_mod = HH;
                ++format;
            }
            break;
        }
        case 'j':
            flags->length_mod = J;
            ++format;
            break;
        case 't':
            flags->length_mod = T;
            ++format;
            break;
        case 'z':
            flags->length_mod = Z;
            ++format;
            break;
        case '\0':
            buffer->error = true;
        default:
            break;
    }
}

flags_t gather_flags(buffer_t* buffer, const char* restrict format, va_list ap) {
    flags_t ret;
    ft_bzero(&ret, sizeof(flags_t));

    set_mod_flags(buffer, format, &ret);
    set_width(buffer, format, ap, &ret);
    set_precision(buffer, format, ap, &ret);
    set_length_mod(buffer, format, &ret);

    return ret;
}
