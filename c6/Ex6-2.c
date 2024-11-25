#include <stdio.h>
#include <stdlib.h>

#define MAXLINE     1000
#define PREF_LEN    6
#define MAXSTRUCT   10 
#define MAXGROUPS   30
enum state {DEFAULT, STRING, STAR_COMMENT};

struct tnode {
    char *prefix;
    int count;
    struct tnode *left;
    struct tnode *right;
};

void remove_comments_and_strings(char *line, int *state);
void scan_for_structs_and_vars(char *line, struct tnode *root);
void print_results(struct tnode *root);

int main(void) {
    size_t line_lim = MAXLINE;
    char *line = (char *)malloc(sizeof(char) * line_lim);
    char *types[MAXSTRUCT + 4];
    int types_num = 4;

    struct tnode *root;

    int state;

    state = DEFAULT;
    while (getline(&line, &line_lim, stdin) > 0) {
        remove_comments_and_strings(line, &state);
        scan_for_structs_and_vars(line, root);
    }

    /*print_results(root);*/
}

void remove_comments_and_strings(char *line, int *state) {
    char *start = line;
    char *p = line; 
    int backslashes = 0;

    while (*line != '\n') {
        if (*state == DEFAULT) {
            if (*line == '/') {
                if (*(line + 1) == '*') {
                    line += 2;
                    *state = STAR_COMMENT;
                } else if (*(line + 1) == '/') {
                    break;
                } else {
                    *p++ = *line++;
                }
            } else if (*line == '"') {
                if (*(line - 1) != '\'' || *(line + 1) != '\'') {
                    *state = STRING;
                }
                *p++ = *line++;
            } else {
                *p++ = *line++;
            }
        } else if (*state == STAR_COMMENT) {
            if (*line == '*') {
                if (*(line + 1) == '/') {
                    line += 2;
                    *state = DEFAULT;
                } else {
                    line++;
                }
            } else {
                line++;
            }
        } else if (*state == STRING) {
            if (*line == '\\') {
                backslashes++;
                line++;
            } else if (*line == '"') {
                if (backslashes % 2 == 0) {
                    *p++ = *line++;
                    *state = DEFAULT;
                } else {
                    backslashes = 0;
                    line++;
                }
            } else {
                line++;
            }
        }
    }
    *p = '\0';
}
