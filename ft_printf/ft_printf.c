#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include "ft_clib.h"
#include "ft_printf_private.h"

pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

int ft_vprintf(const char* restrict format, va_list ap) {
    pthread_mutex_lock(&g_lock);
    buffer_t buffer;
    ft_bzero(&buffer, sizeof(buffer));

    buffer.fd = STDOUT_FILENO;

    print_loop(&buffer, format, ap);

    pthread_mutex_unlock(&g_lock);
    return buffer.error ? -1 : buffer.ret;
}

int ft_vfprintf(FILE* restrict stream, const char* restrict format, va_list ap) {
    pthread_mutex_lock(&g_lock);
    buffer_t buffer;
    ft_bzero(&buffer, sizeof(buffer));

    buffer.fd = fileno(stream);

    print_loop(&buffer, format, ap);

    pthread_mutex_unlock(&g_lock);
    return buffer.error ? -1 : buffer.ret;
}

int ft_vsprintf(char* restrict str, const char* restrict format, va_list ap) {
    pthread_mutex_lock(&g_lock);
    buffer_t buffer;
    ft_bzero(&buffer, sizeof(buffer));

    buffer.is_string = true;
    buffer.str_data.str = str;
    buffer.str_data.max_size = (size_t)INT_MAX + 1;

    print_loop(&buffer, format, ap);

    pthread_mutex_unlock(&g_lock);
    return buffer.error ? -1 : buffer.ret;
}

int ft_vsnprintf(char* restrict str, size_t size, const char* restrict format, va_list ap) {
    pthread_mutex_lock(&g_lock);
    buffer_t buffer;
    ft_bzero(&buffer, sizeof(buffer));

    buffer.is_string = true;
    buffer.str_data.str = str;
    buffer.str_data.max_size = size == 0 ? 0 : size - 1;

    print_loop(&buffer, format, ap);
    if (size != 0) {
        buffer.str_data.str[buffer.str_data.str_index] = '\0';
    }

    pthread_mutex_unlock(&g_lock);
    return buffer.error ? -1 : buffer.ret;
}

// int vasprintf(char** ret, const char*format, va_list ap);

int ft_vdprintf(int fd, const char* restrict format, va_list ap) {
    pthread_mutex_lock(&g_lock);
    buffer_t buffer;
    ft_bzero(&buffer, sizeof(buffer));

    buffer.fd = fd;

    print_loop(&buffer, format, ap);

    pthread_mutex_unlock(&g_lock);
    return buffer.error ? -1 : buffer.ret;
}

int ft_printf(const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vprintf(format, ap);
    va_end(ap);
    return ret;
}

int ft_fprintf(FILE* restrict stream, const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfprintf(stream, format, ap);
    va_end(ap);
    return ret;
}

int ft_sprintf(char* restrict str, const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vsprintf(str, format, ap);
    va_end(ap);
    return ret;
}

int ft_snprintf(char* restrict str, size_t size, const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vsnprintf(str, size, format, ap);
    va_end(ap);
    return ret;
}

// asprintf(char** ret, const char* format, ...);

int ft_dprintf(int fd, const char* restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int ret = ft_vdprintf(fd, format, ap);
    va_end(ap);
    return ret;
}


