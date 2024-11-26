#include <ctype.h>
#include <stdio.h>

void convert(int tocase(int));

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: tocase [CASE]\n"
               "\tCASE:\n"
               "\t\tl - lower\n"
               "\t\tu - uper\n");
        return 1;
    }

    if (argv[1][0] == 'l' || argv[1][0] == 'u')
        convert(*argv[1] == 'l' ? tolower : toupper);

    return 0;
}

void convert(int tocase(int)) {
    int c;

    while ((c = getchar()) != EOF) {
        putchar(tocase(c));
    }
}
