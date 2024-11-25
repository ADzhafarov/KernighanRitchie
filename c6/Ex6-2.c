#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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
void scan_for_structs_and_vars(char *line, struct tnode **root, char *types[], int *types_num);
void print_results(struct tnode *root);
void print_types(char *types[], int types_num);
void initialize_types(char *types[], int *types_num);
void print_results(struct tnode *p);


int main(void) {
    size_t line_lim = MAXLINE;
    char *line = (char *)malloc(sizeof(char) * line_lim);
    char *types[MAXSTRUCT + 4];
    int types_num = 0;

    initialize_types(types, &types_num);
    struct tnode *root = NULL;

    int state;

    state = DEFAULT;
    while (getline(&line, &line_lim, stdin) > 0) {
        remove_comments_and_strings(line, &state);
        scan_for_structs_and_vars(line, &root, types, &types_num);
    }

    if (root == NULL) {
        printf("NULL\n");
    }

    print_types(types, types_num);
    print_results(root);
}

void initialize_types(char *types[], int *types_num) {
    types[0] = "char";
    types[1] = "int";
    types[2] = "float";
    types[3] = "double";
    *types_num = 4;
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
                backslashes = 0;
                line++;
            }
        }
    }
    *p = '\0';
}

#define MAXWORD     20
int getword(char **line, char *word, int lim);
void add_type_if_new(char *word, char *types[], int *types_num);
struct tnode *add_group(char *word, struct tnode *root);
void inc_group(char *word, struct tnode *root);
void define_word_type(char *word, int *cur_word, char *types[], int types_num);

enum word_types {STRUCT, TYPE, ALPHANUM, NAW};

// Limitation: we suggest code that always tags structures and declares variables of these structures by tag;
void scan_for_structs_and_vars(char *line, struct tnode **root, char *types[], int *types_num) {
    char word[MAXWORD];
    int cur_word, prev_word;
    prev_word = -1;

    while ((cur_word = getword(&line, word, MAXWORD)) != EOF) {
        if (cur_word == ALPHANUM) {
            define_word_type(word, &cur_word, types, *types_num);
            if (prev_word == STRUCT) { 
                add_type_if_new(word, types, types_num);
                cur_word = TYPE;
            } else if (prev_word == TYPE) {
                *root = add_group(word, *root);
            } else {
                inc_group(word, *root);
            }
            prev_word = cur_word;
        }
    }
}

void add_type_if_new(char *word, char *types[], int *types_num) {
    for (int i = 0; i < *types_num; i++) {
        if (strcmp(word, types[i]) == 0) {
            return;
        }
    }
    if (*types_num >= MAXSTRUCT + 4) {
        printf("add_types_if_new error: too many structs\n");
        return;
    }

    char *p = (char *)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(p, word);
    types[((*types_num)++)] = p;
}

struct tnode *add_group(char *word, struct tnode *p) {
    int comp;

    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->prefix = (char *)malloc(sizeof(char) * (PREF_LEN + 1));
        strncpy(p->prefix, word, PREF_LEN);
        p->count = 1;
        p->right = NULL;
        p->left = NULL;
        return p;
    } else if ((comp = strncmp(word, p->prefix, PREF_LEN)) < 0)
        p->left = add_group(word, p->left);
    else if (comp > 0)
        p->right = add_group(word, p->right);
    else
        p->count++;
    return p;
}

void inc_group(char *word, struct tnode *root) {
    int comp;

    if (root == NULL) {
        return;
    } else if ((comp = strncmp(word, root->prefix, PREF_LEN)) < 0)
        inc_group(word, root->left);
    else if (comp > 0)
        inc_group(word, root->right);
    else
        root->count++;
}

void define_word_type(char *word, int *cur_word, char *types[], int types_num) {
    if (strcmp(word, "struct") == 0) {
        *cur_word = STRUCT;
        return;
    }

    for (int i = 0; i < types_num; i++) {
        if (strcmp(word, types[i]) == 0) {
            *cur_word = TYPE;
            return;
        }
    }
    return;
}

int getword(char **line, char *word, int lim) {
    while (isblank(**line))
        (*line)++;

    if (**line == '\0')
        return EOF;

    if (!isalpha(*word++ = **line)) {
        *word = '\0';
        (*line)++;
        return NAW; 
    } else {
        (*line)++;
    }

    while (isalnum(*word++ = *(*line)++))
        ;
    *(word-1) = '\0';
    (*line)--;

    return ALPHANUM;
}

void print_results(struct tnode *p) {
    if (p == NULL)
        return;
    print_results(p->left);
    printf("%4d\t%s\n", p->count, p->prefix);
    print_results(p->right);
}

void print_types(char *types[], int types_num) {
    for (int i = 0; i < types_num; i++)
        printf("%s%s", types[i], i == types_num - 1 ? "\n" : ", ");
}
