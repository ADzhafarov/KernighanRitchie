#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

void expose(void);
void undef(char *);

int main(void) {
    install("1", "one");
    install("2", "two");
    install("3", "three");
    install("4", "four");
    install("5", "five");
    install("6", "six");
    expose();
    undef("6");
    expose();
    undef("5");
    expose();
    undef("4");
    expose();
    undef("3");
    expose();
    undef("2");
    expose();
    undef("1");
    expose();
}

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};



#define HASHSIZE    101

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
    for (int i = 0; i < HASHSIZE; i++)
        for (p = hashtab[i]; p != NULL; p=p->next)
            printf("%5s:\t%s\n", p->name, p->defn);

    printf("\n");
}
