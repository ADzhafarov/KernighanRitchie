#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES	5000
char *lineptr[MAXLINES];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(void *lineptr[], int left, int right, int (*comp)(const void *, const void *), int order);
int numcmp(const char *, const char *);

int main(int argc, char *argv[]) {
	int nlines;
	int c;
	int numeric = 0;
	int order = 1;
	
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					order = -1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					break;
			}
	if (argc != 1)
		printf("Usage: sort [OPTIONS]");
	else {
		if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
			myqsort((void **) lineptr, 0, nlines - 1,
		   (int (*)(const void *, const void *))(numeric ? numcmp : strcmp), order);
			writelines(lineptr, nlines);
			return 0;
		} else {
			printf("input too big to sort\n");
			return 1;
		}
	}
}

void myqsort(void *v[], int left, int right, int (*comp)(const void *, const void *), int order) {
	int i, last;

	void swap(void *v[], int i, int j);

	if (left >= right)
		return;
	
	swap(v, left, (left + right) / 2);
	last = left;
	
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) * order < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	myqsort(v, left, last - 1, comp, order);
	myqsort(v, last + 1, right, comp, order);
}

int numcmp(const char *s1, const char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#define MAXLEN		10001
int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

#define ALLOCSIZE	500000000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

void afree(char *p) {
	if (p > allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

int get_line(char s[], int lim) {
	int c, i;

	for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
