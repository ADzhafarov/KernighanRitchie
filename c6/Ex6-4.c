#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE             1000
#define MAXLINES            1000
#define MAXDISTINCTWORDS    1000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct count_tnode {
    int count;
    char **words;
    int wc;
    struct count_tnode *left;
    struct count_tnode *right;
};

enum word_types {ALPHANUM = 1, NAW};

void print_results(struct count_tnode *p);
void process_line(char *line, struct tnode **p, int *max_occurences);

struct count_tnode *initialize_count_node(int val);
void redistribute_results(struct tnode *p, struct count_tnode **count_p);

int main(void) {
    size_t line_lim = MAXLINE;
    char *line = (char *)malloc(sizeof(char) * line_lim);
    int max_occurences = 0;

    struct tnode *root = NULL;

    while (getline(&line, &line_lim, stdin) > 0) {
        process_line(line, &root, &max_occurences);
    }

    struct count_tnode *c_root = initialize_count_node(max_occurences / 2);
    redistribute_results(root, &c_root);

    print_results(c_root);
}

struct count_tnode *add_count(char *word, int count, struct count_tnode *count_p);

void redistribute_results(struct tnode *p, struct count_tnode **count_p) {
    if (p == NULL) {
        return;
    } else {
        redistribute_results(p->left, count_p);
        redistribute_results(p->right, count_p);
        *count_p = add_count(p->word, p->count, *count_p);
    }
}

struct count_tnode *add_count(char *word, int count, struct count_tnode *count_p) {
    if (count_p == NULL) {
        count_p = initialize_count_node(count);
        count_p->words[count_p->wc++] = word;
    } else if (count < count_p->count) {
        count_p->left = add_count(word, count, count_p->left);
    } else if (count > count_p->count) {
        count_p->right = add_count(word, count, count_p->right);
    } else {
        count_p->words[count_p->wc++] = word;
    }
    return count_p;
}

struct count_tnode *initialize_count_node(int val) {
    struct count_tnode *p;
    p = (struct count_tnode *)malloc(sizeof(struct count_tnode));
    p->count = val;
    p->words = (char **)malloc(sizeof(char *) * (MAXDISTINCTWORDS));
    p->wc = 0;
    p->left = NULL;
    p->right = NULL;
    return p;
}

#define MAXWORD     20
int getword(char **line, char *word, int lim);
void add_type_if_new(char *word, char *types[], int *types_num);
struct tnode *add_group(char *word, struct tnode *root);
void inc_group(char *word, struct tnode *root);
void define_word_type(char *word, int *cur_word, char *types[], int types_num);

struct tnode *add_word_occurence(struct tnode *p, char *word, int *max_occurences);

void process_line(char *line, struct tnode **p, int *max_occurences) {
    char word[MAXWORD];
    int word_type;
    while ((word_type = getword(&line, word, MAXWORD)) != EOF) {
        if (word_type == ALPHANUM) {
            *p = add_word_occurence(*p, word, max_occurences);
        }
    }
}

#define max(A, B)   ((A) > (B)) ? (A) : (B)

struct tnode *add_word_occurence(struct tnode *p, char *word, int *max_occurences) {
    int comp;
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = (char *)malloc(sizeof(char) * (MAXWORD + 1));
        strcpy(p->word, word);
        p->count = 1;
        *max_occurences = max(*max_occurences, p->count);
        p->left = NULL;
        p->right = NULL;
    } else if ((comp = strcmp(word, p->word)) < 0) {
        p->left = add_word_occurence(p->left, word, max_occurences);
    } else if (comp > 0) {
        p->right = add_word_occurence(p->right, word, max_occurences);
    } else {
        p->count++;
        *max_occurences = max(*max_occurences, p->count);
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

void print_results(struct count_tnode *p) {
    if (p == NULL)
        return;
    print_results(p->right);
    for (int i = 0; i < p->wc; i++) {
        printf("%4d\t%s\n", p->count, p->words[i]);
    }
    print_results(p->left);
}


