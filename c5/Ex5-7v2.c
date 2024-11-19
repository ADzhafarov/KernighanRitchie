#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAXLINES	50000
#define MAXLEN		10001
#define MAXSTORE	1000000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *linestore);
void writelines(char *lineptr[], int nlines);

void qsort(char *v[], int left, int right);

int main(void) {
	int nlines;
	char linestore[MAXSTORE];
	
	clock_t t0 = clock();
	if ((nlines = readlines(lineptr, MAXLINES, linestore)) >= 0) {
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		clock_t t1 = clock();
		printf("V2:\t\t%f\n", (float)(t1 - t0) / CLOCKS_PER_SEC);
		return 0;
	} else {
		printf("error: input is too big to sort\n");
		return 1;
	}
}

int get_line(char *, int);

int readlines(char *lineptr[], int maxlines, char *linestore) {
	int len, nlines;
	char line[MAXLEN];
	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines || strlen(linestore) + len > MAXSTORE) {
			return -1;
		} else {
			line[len-1] = '\0';
			printf("%d %d\n", nlines, len);
			strcpy(linestore, line);
			printf("%d %d\n", nlines, len);
			lineptr[nlines++] = linestore;
			linestore += len;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
