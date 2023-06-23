#include <stdio.h>
#include "ft_printf.h"
#include "ft_clib.h"
#include <string.h>

int main() {
    WARN("hoi");
    char buf[20];
    bzero(buf, 20);
    ft_sprintf(buf, "hoi % #*.*hhd doei", -5, 4, 3);
    printf("%s\n", buf);
}