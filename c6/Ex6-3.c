#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     1000
#define MAXLINES    1000

struct tnode {
    char *word;
    int *lines;
    int lines_num;
    struct tnode *left;
    struct tnode *right;
};

enum word_types {ALPHANUM = 1, NAW};

void print_results(struct tnode *p);
void process_line(char *line, struct tnode **p, int line_num);

int main(void) {
    size_t line_lim = MAXLINE;
    char *line = (char *)malloc(sizeof(char) * line_lim);
    int line_num = 1;

    struct tnode *root = NULL;

    while (getline(&line, &line_lim, stdin) > 0) {
        process_line(line, &root, line_num++);
    }

    print_results(root);
}

#define MAXWORD     20
int getword(char **line, char *word, int lim);
void add_type_if_new(char *word, char *types[], int *types_num);
struct tnode *add_group(char *word, struct tnode *root);
void inc_group(char *word, struct tnode *root);
void define_word_type(char *word, int *cur_word, char *types[], int types_num);

struct tnode *add_word_occurence(struct tnode *p, char *word, int line_num);

void process_line(char *line, struct tnode **p, int line_num) {
    char word[MAXWORD];
    int word_type;
    while ((word_type = getword(&line, word, MAXWORD)) != EOF) {
        if (word_type == ALPHANUM) {
            *p = add_word_occurence(*p, word, line_num);
        }
    }
}

struct tnode *add_word_occurence(struct tnode *p, char *word, int line_num) {
    int comp;
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = (char *)malloc(sizeof(char) * (MAXWORD + 1));
        strcpy(p->word, word);
        p->lines = (int *)malloc(sizeof(int) * (MAXLINES));
        p->lines[0] = line_num;
        p->lines_num = 1;
        p->left = NULL;
        p->right = NULL;
    } else if ((comp = strcmp(word, p->word)) < 0) {
        p->left = add_word_occurence(p->left, word, line_num);
    } else if (comp > 0) {
        p->right = add_word_occurence(p->right, word, line_num);
    } else if (p->lines_num < MAXLINES) {
        p->lines[p->lines_num++] = line_num;
    }
    return p;
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

static char *filterwords[] = {"is", "and", "the", "of", "if", "at", "in"};
#define FILTERNUM   (sizeof(filterwords)) / (sizeof(*filterwords))

void print_results(struct tnode *p) {
    int i;
    char found = 0;
    char *pt;
    if (p == NULL)
        return;
    print_results(p->left);


    pt = *filterwords;
    for (i = 0; i < FILTERNUM; i++) {
        if (strcmp(p->word, pt + i) == 0)
            found = 1;
    }

    if (found == 0) {
        printf("%20s:\t", p->word);
        for (i = 0; i < p->lines_num; i++) {
            if (found == 0)
                printf("%d%s", p->lines[i], i == p->lines_num - 1 ? "\n": ", ");
        }
    }

    print_results(p->right);
}

