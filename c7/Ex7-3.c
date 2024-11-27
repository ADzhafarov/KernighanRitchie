#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define MAX     1000
void minprintf(char *fmt, ...);
int doublelen(double num);

int main(void) {
    minprintf("%-10d\n", 100);
    minprintf("%10d\n", 100);
    minprintf("%-10s\n", "str");
    minprintf("%10s\n", "str");
    minprintf("%-10f\n", .100);
    minprintf("%10f\n", .100);
    minprintf("%c\n", '0');
}

int intlen(int num, int base);

void minprintf(char *fmt, ...) {
    va_list ap;
    char cval, *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        int i, s_len;
        char left_align = 0;
        int alignval = 0;
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        if (*++p == '-') {
            left_align = 1;
        } else
            p--;

        while (isdigit(*++p))
            alignval = alignval * 10 + (*p - '0');

        printf("left alignment: %d\n", left_align);
        printf("alignment: %d\n", alignval);
        switch(*p) {
            case 'd':
                ival = va_arg(ap, int);
                if (alignval > 0 && left_align == 0) {
                    for (i = 0; i < alignval - intlen(ival, 10); i++)
                        putchar(' ');
                }
                printf("%d", ival);
                if (alignval > 0 && left_align == 1) {
                    for (i = 0; i < alignval - intlen(ival, 10); i++)
                        putchar(' ');
                }
                break;
            case 'f':
                dval = va_arg(ap, double);
                if (alignval > 0 && left_align == 0) {
                    for (i = 0; i < alignval - doublelen(dval); i++)
                        putchar(' ');
                }
                printf("%f", dval);
                if (alignval > 0 && left_align == 1) {
                    for (i = 0; i < alignval - doublelen(dval); i++)
                        putchar(' ');
                }
                break;
            case 'c':
                cval = va_arg(ap, unsigned);
                putchar(cval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                s_len = strlen(sval);
                if (alignval > 0 && left_align == 0) {
                    for (i = 0; i < alignval - s_len; i++)
                        putchar(' ');
                }
                for (; *sval; sval++)
                    putchar(*sval);
                if (alignval > 0 && left_align == 1) {
                    for (i = 0; i < alignval - s_len; i++)
                        putchar(' ');
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }
}

int intlen(int num, int base) {
    int res = 0;

    do {
        res += 1;
        num /= base;
    } while (num > 0);

    return res;
}

int doublelen(double num) {
    int res = 7;
    if (num < 0) {
        res++;
        num = -num;
    }

    int inum = (int) num;

    do {
        res += 1;
        inum /= 10;
    } while (inum > 0);

    return res;
}
