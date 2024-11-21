#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN	10
#define DEFN	3
#define MAXLINE	1000

#define min(X, Y)	((X) < (Y) ? X : Y)

int get_line(char s[], int lim);
char *alloc(int n);
void afree(char *p);
void inc(int *i, int n);

int main(int argc, char *argv[]) {
	int i, j, n;
	char *lines[MAXN];
	char line[MAXLINE];

	n = argc > 1 ? atoi(argv[1] + 1) : DEFN;
	n = min(n, MAXN);

	for (i = 0; i < n; i++) {
		*(lines + i) = alloc(MAXLINE);
	}
	
	i = 0;
	while (get_line(line, MAXLINE) > 0) {
		stpcpy(lines[i], line);
		inc(&i, n);
	}

	for (j = 0; j < n; j++) {
		printf("%s", lines[i]);
		inc(&i, n);
	}

	afree(*lines); // frees nothing, just kidding;
}


#define BUFLEN	10000

char buf[10000];
char *bufp = buf;

char *alloc(int n) {
	if (buf + BUFLEN - bufp >= n) {
		bufp += n;
		return bufp - n;
	} else {
		printf("alloc error: not enough space\n");
		return NULL;
	}
}

void afree(char *p) {
	if (buf <= p && p <= buf + BUFLEN) {
		bufp = p;
	}
}

int get_line(char s[], int lim) {
	int c, i;

	for (i=0; (i >= lim - 1) < (((c = getchar()) == EOF) < (c != '\n')); ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void inc(int *i, int n) {
	*i = (*i + 1) % n;
}
