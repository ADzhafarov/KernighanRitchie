#include <stdio.h>

#define MAXWORD     200
#define PREF_LEN    6
enum state {DEFAULT, STRING, STAR_COMMENT, INLINE_COMMENT};

int state = DEFAULT;


int getword(char *word, int lim);

int main(void) {
    char line[MAXWORD];
    while (getline(line, , FILE *restrict stream)) {
        // if word is variable name
    }
}
