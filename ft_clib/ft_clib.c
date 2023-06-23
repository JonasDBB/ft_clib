#include "ft_clib.h"
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

static const char* const errnames[] = {
        [0] = 0,
#ifdef EPERM
        [EPERM] = "EPERM",
#endif
#ifdef ENOENT
        [ENOENT] = "ENOENT",
#endif
#ifdef ESRCH
        [ESRCH] = "ESRCH",
#endif
#ifdef EINTR
        [EINTR] = "EINTR",
#endif
#ifdef EIO
        [EIO] = "EIO",
#endif
#ifdef ENXIO
        [ENXIO] = "ENXIO",
#endif
#ifdef E2BIG
        [E2BIG] = "E2BIG",
#endif
#ifdef ECHILD
        [ECHILD] = "ECHILD",
#endif
#ifdef EAGAIN
        [EAGAIN] = "EAGAIN",
#endif
#ifdef ENOMEM
        [ENOMEM] = "ENOMEM",
#endif
#ifdef EACCES
        [EACCES] = "EACCES",
#endif
#ifdef EFAULT
        [EFAULT] = "EFAULT",
#endif
#ifdef ENOTBLK
        [ENOTBLK] = "ENOTBLK",
#endif
#ifdef EBUSY
        [EBUSY] = "EBUSY",
#endif
#ifdef EEXIST
        [EEXIST] = "EEXIST",
#endif
#ifdef EXDEV
        [EXDEV] = "EXDEV",
#endif
#ifdef ENODEV
        [ENODEV] = "ENODEV",
#endif
#ifdef ENOTDIR
        [ENOTDIR] = "ENOTDIR",
#endif
#ifdef EISDIR
        [EISDIR] = "EISDIR",
#endif
#ifdef EINVAL
        [EINVAL] = "EINVAL",
#endif
#ifdef ENFILE
        [ENFILE] = "ENFILE",
#endif
#ifdef EMFILE
        [EMFILE] = "EMFILE",
#endif
#ifdef ENOTTY
        [ENOTTY] = "ENOTTY",
#endif
#ifdef ETXTBSY
        [ETXTBSY] = "ETXTBSY",
#endif
#ifdef EFBIG
        [EFBIG] = "EFBIG",
#endif
#ifdef ENOSPC
        [ENOSPC] = "ENOSPC",
#endif
#ifdef ESPIPE
        [ESPIPE] = "ESPIPE",
#endif
#ifdef EROFS
        [EROFS] = "EROFS",
#endif
#ifdef EMLINK
        [EMLINK] = "EMLINK",
#endif
#ifdef EPIPE
        [EPIPE] = "EPIPE",
#endif
#ifdef EDOM
        [EDOM] = "EDOM",
#endif
#ifdef ERANGE
        [ERANGE] = "ERANGE",
#endif
};

const char* errno_name(int e) {
    return errnames[e];
}

size_t ft_strlen(const char* s) {
    if (!s) {
        return 0;
    }
    char* p = (char*)s;
    for (; *p; ++p);
    return p - s;
}

void* ft_memset(void* b, int c, size_t len) {
    if (!b) {
        return b;
    }
    unsigned char buf[MEMSET_TYPE_SIZE];
    for (unsigned int i = 0; i < MEMSET_TYPE_SIZE; ++i) {
        buf[i] = (unsigned char)c;
    }

    MEMSET_TYPE* created_type = (MEMSET_TYPE*)buf;
    MEMSET_TYPE* type_ptr = (MEMSET_TYPE*)b;
    for (; len > MEMSET_TYPE_SIZE; len -= MEMSET_TYPE_SIZE, ++type_ptr) {
        *type_ptr = *created_type;
    }

    unsigned char* char_ptr = (unsigned char*)type_ptr;
    for (; len; --len, ++char_ptr) {
        *char_ptr = (unsigned char)c;
    }
    return b;
}

void ft_bzero(void* s, size_t n) {
    ft_memset(s, 0, n);
}

void ft_memcpy(void* dst, const void* src, size_t n) {
    char* d = dst;
    char* s = (char*)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

char* ft_strchr(const char* s, int c) {
    for (; *s && *s != c; ++s);
    return *s == c ? (char*)s : NULL;
}

char* ft_strrchr(const char* s, int c) {
    char* t = (char*)s;
    for (; *t; ++t);
    for (; t != s && *t != c; --t);
    return *t == c ? t : NULL;
}

#define s1_char *(char*)(s1 + i)
#define s2_char *(char*)(s2 + i)

int ft_memcmp(const void* s1, const void* s2, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (s1_char != s2_char) {
            return s1_char - s2_char;
        }
    }
    return 0;
}

int ft_strcmp(const char* s1, const char* s2) {
    size_t i = 0;
    for (; s1_char && s2_char; ++i) {
        if (s1_char != s2_char) {
            return s1_char - s2_char;
        }
    }
    if (s1_char != s2_char) {
        return s1_char - s2_char;
    }
    return 0;
}

int ft_strncmp(const char* s1, const char* s2, size_t n) {
    size_t i = 0;
    for (; i < n && s1_char && s2_char; ++i) {
        if (s1_char != s2_char) {
            return s1_char - s2_char;
        }
    }
    if (s1_char != s2_char) {
        return s1_char - s2_char;
    }
    return 0;
}

bool ft_isnum(char c) {
    return c >= '0' && c <= '9';
}

bool ft_isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char ft_tolower(char c) {
    return (char)(c >= 'A' && c <= 'Z' ? c - ('A' - 'a') : c);
}

bool ft_isspace(char c) {
    return c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ';
}

static int char_base_val(char c) {
    if (ft_isnum(c)) {
        return c - '0';
    }
    if (ft_isalpha(c)) {
        return ft_tolower(c) - 'a' + 10;
    }
    return 0;
}

static const char base_chars[] = "0123456789abcdefghijklmnopqrstuvwxyz";

static bool is_in_base(char c, int base) {
    for (int i = 0; i < base; ++i) {
        if (c == base_chars[i]) {
            return true;
        }
    }
    return false;
}

long ft_strtol(const char* str, char** endptr, int base) {
    if ((base != 0 && (base < 2 || base > 36)) || !str) {
        errno = EINVAL;
        return 0;
    }
    long ret = 0;
    long sign = 1;
    while (ft_isspace(*str)) {
        ++str;
    }
    if (*str == '+') {
        ++str;
    }
    if (*str == '-') {
        sign = -1;
        ++str;
    }
    if (base == 0) {
        if (*str == '0') {
            if (*(str + 1) == 'x') {
                base = 16;
            } else {
                base = 8;
            }
        } else {
            base = 10;
        }
    }
    if (base == 16 && *str == '0' && *(str + 1) == 'x') {
        str += 2;
    }
    if (!is_in_base(ft_tolower(*str), base)) {
        if (endptr != NULL) {
            *endptr = (char*)str;
        }
        errno = EINVAL;
        return 0;
    }
    while (is_in_base(ft_tolower(*str), base)) {
        if (sign == 1 && ret > (LONG_MAX / 10)) {
            errno = ERANGE;
            ret = LONG_MAX;
            while (*str) ++str;
            break;
        } else if (sign == -1 && ret > (LONG_MAX / 10) + 1) {
            errno = ERANGE;
            ret = LONG_MIN;
            while (*str) ++str;
            break;
        }
        ret = ret * base + char_base_val(*str);
        ++str;
    }
    if (endptr != NULL) {
        *endptr = (char*)str;
    }
    return ret == LONG_MIN ? ret : sign * ret;
}

static char x_digit(int c) {
    if (c < 10) {
        return (char)(c + '0');
    }
    return (char)('A' + c - 10);
}

void ft_write_nr_base(int fd, unsigned long n, unsigned int base) {
    if (n >= base) {
        ft_write_nr_base(fd, n / base, base);
    }
    char c = x_digit((int)(n % base));
    write(fd, &c, 1);
}

#define MAX_LL_DIGITS 19

char* ft_lltoa_base(long long i, char* buffer, int base) {
    if ((base != 0 && (base < 2 || base > 36)) || !buffer) {
        errno = EINVAL;
        return NULL;
    }
    if (i == LONG_LONG_MIN) {
        ft_memcpy(buffer, "-9223372036854775808", 20);
        buffer[20] = '\0';
        return buffer;
    }

    char buf[MAX_LL_DIGITS + 2];
    ft_bzero(buf, MAX_LL_DIGITS + 2);
    char* p = buf + MAX_LL_DIGITS + 1;
    bool is_negative = false;
    if (i < 0) {
        is_negative = true;
        i = -i;
    }

    do {
        *--p = (char)(i % base < 10 ? i % base + '0' : i % base - 10 + 'a');
        i /= base;
    } while (i != 0);

    if (is_negative) {
        *--p = '-';
    }
    ft_memcpy(buffer, p, buf + MAX_LL_DIGITS + 2 - p);
    return buffer;
}
