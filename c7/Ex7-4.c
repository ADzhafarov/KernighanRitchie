#include <stdarg.h>
#include <stdio.h>

int minscanf(char *fmt, ...);

int main(void) {
    int day, year;
    char month[10];
    
    printf("Enter a date: ");
    printf("scaned %d variables\n", minscanf("%d %s %d", &day, month, &year));

    printf("Entered date: %d %s %d\n", day, month, year);

    double f;
    printf("Enter a floating-point value: ");
    minscanf("%f", &f);
    printf("Entered value: %f\n", f);

}

int minscanf(char *fmt, ...) {
    va_list ap;
    char *p;

    int *ival;
    double *dval;
    char *cval;
    char *sval;

    int counter = 0;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                scanf("%d", ival);
                counter++;
                break;
            case 'f':
                dval = va_arg(ap, double *);
                scanf("%lf", dval);
                counter++;
                break;
            case 'c':
                cval = va_arg(ap, char *);
                scanf("%c", cval);
                counter++;
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf("%s", sval);
                counter++;
                break;
            default:
                break;
        }
    }

    return counter;
}
