#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE     200
#define MAXNAME     20

int getword(char **line, char *word, int lim);
struct nlist *install(char *name, char *defn);
void expose(void);

int main(void) {
    char *line = (char *)malloc(MAXLINE + 1);
    char *pt;
    char name[MAXNAME];
    size_t lim = MAXLINE;

    while (getline(&line, &lim, stdin) > 0) {
        if (strncmp(line, "#define", 7) == 0) {
            pt = line + 7;
            if (getword(&pt, name, MAXNAME) != EOF) {
                while (*pt == ' ' || *pt == '\t') {
                    pt++;
                }
                install(name, pt);
            }
        }
    }
    expose();
}

int getword(char **line, char *word, int lim) {
    while (isblank(**line))
        (*line)++;

    if (**line == '\0')
        return EOF;

    if (!isalpha(*word++ = **line)) {
        *word = '\0';
        (*line)++;
        return 1; 
    } else {
        (*line)++;
    }

    while (isalnum(*word++ = *(*line)++))
        ;
    *(word-1) = '\0';
    (*line)--;

    return 1;
}

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE    101
#define HALF        1./.5

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *s) {
    struct nlist **start = &hashtab[hash(s)];
    struct nlist *np;

    struct nlist *prev = NULL;
    for (np = *start; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            if (prev == NULL)
                *start = np->next;
            else
                prev->next = np->next;
            free(np);
            break;
        }
        prev = np;
    }
}

void expose(void) {
    struct nlist *p;
    printf("Hashtable contents:\n");
    for (int i = 0; i < HASHSIZE; i++)
        for (p = hashtab[i]; p != NULL; p=p->next)
            printf("%20s:\t%s\n", p->name, p->defn);

    printf("\n");
}
