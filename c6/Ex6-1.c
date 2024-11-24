#include <stdio.h>
#include <ctype.h>

#define MAXWORD     100

int getword(char * word, int lim);

int main(void) {
    char word[MAXWORD];
    while ((getword(word, MAXWORD)) != EOF)
        printf("%s\n", word);
    return 0;
}

enum state {DEFAULT, STRING};

int getword(char * word, int lim) {
    int c, getch(void);
    void ungetch(int);
    int state = DEFAULT;
    int backslashes;

    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '#' && c != '"') {
        *w = '\0';
        return c;
    }
    state = DEFAULT;
    if (c == '"') {
        state = STRING;
        backslashes = 0;
    }
    for ( ; --lim > 0; w++)
        if (state == DEFAULT) {
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
        } else if (state == STRING) {
            if ((*w = getch()) == '"') {
                if (backslashes % 2 == 1) {
                    state = DEFAULT;
                    backslashes = 0;
                    w++;
                    break;
                }
            } else if (*w == '/')
                backslashes++;
            else
                backslashes = 0;
        }

    *w = '\0';
    return word[0];
}

int buf;

int getch(void) {
    int temp;

    if (buf == -1)
        return getchar();
    else {
        temp = buf;
        buf = -1;
        return temp;
    }
}

void ungetch(int c) {
    buf = c;
}


