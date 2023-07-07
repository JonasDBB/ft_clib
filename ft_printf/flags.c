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

static bool set_mod_flags(const char* restrict* format, flags_t* flags) {
    while (*format && is_mod_flag(**format)) {
        set_mod_flag(flags, **format);
        ++(*format);
    }
    if (*format == 0) {
        return true;
    }
    return false;
}

static bool set_width(const char* restrict* format, va_list ap, flags_t* flags) {
    if (**format == '*') {
        int width_arg = va_arg(ap, int);
        if (width_arg < 0) {
            flags->minus = true;
            width_arg = -width_arg;
        }
        flags->field_width = width_arg;
        ++(*format);
    } else if (ft_isnum(**format)) {
        char* inc;
        flags->field_width = ft_strtol(*format, &inc, 10);
        *format = inc;
    }
    if (*format == 0) {
        return true;
    }
    return false;
}

static bool set_precision(const char* restrict* format, va_list ap, flags_t* flags) {
    if (**format != '.') {
        return false;
    }
    flags->has_precision = true;
    ++(*format);
    if (**format == '*') {
        int precision_arg = va_arg(ap, int);
        if (precision_arg > 0) {
            flags->precision = precision_arg;
        }
        ++(*format);
    } else if (ft_isnum(**format)) {
        char* inc;
        flags->precision = ft_strtol(*format, &inc, 10);
        *format = inc;
    }
    if (*format == 0) {
        return true;
    }
    return false;
}

static bool set_length_mod(const char* restrict* format, flags_t* flags) {
    switch (**format) {
        case 'l': {
            flags->length_mod = L;
            ++(*format);
            if (**format == 'l') {
                flags->length_mod = LL;
                ++(*format);
            }
            break;
        }
        case 'h': {
            flags->length_mod = H;
            ++(*format);
            if (**format == 'h') {
                flags->length_mod = HH;
                ++(*format);
            }
            break;
        }
        case 'j':
            flags->length_mod = J;
            ++(*format);
            break;
        case 't':
            flags->length_mod = T;
            ++(*format);
            break;
        case 'z':
            flags->length_mod = Z;
            ++(*format);
            break;
        case '\0':
            return true;
        default:
            break;
    }
    return false;
}

flags_t gather_flags(buffer_t* buffer, const char* restrict* format, va_list ap) {
    flags_t ret;
    ft_bzero(&ret, sizeof(flags_t));

    buffer->error = set_mod_flags(format, &ret);
    buffer->error = set_width(format, ap, &ret);
    buffer->error = set_precision(format, ap, &ret);
    buffer->error = set_length_mod(format, &ret);

    return ret;
}
