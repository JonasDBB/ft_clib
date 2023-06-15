#ifndef CLIB_TEST_FT_PRINTF_H
#define CLIB_TEST_FT_PRINTF_H

int ft_vprintf(const char* restrict format, va_list ap);
int ft_vfprintf(FILE* restrict stream, const char* restrict format, va_list ap);
int ft_vsprintf(char* restrict str, const char* restrict format, va_list ap);
int ft_vsnprintf(char* restrict str, size_t size, const char* restrict format, va_list ap);
int ft_vdprintf(int fd, const char* restrict format, va_list ap);
int ft_printf(const char* restrict format, ...);
int ft_fprintf(FILE* restrict stream, const char* restrict format, ...);
int ft_sprintf(char* restrict str, const char* restrict format, ...);
int ft_snprintf(char* restrict str, size_t size, const char* restrict format, ...);
int ft_dprintf(int fd, const char* restrict format, ...);

#endif
