#include <ctype.h>
#include <stdio.h>

#define SIZE	100

int getint(int *pn);

int main(void) {
	int i, n, array[SIZE];

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;

	for (i = 0; i < n; i++)
		printf("%d\n", array[i]);
}

int getch(void);
void ungetch(int);

int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
		// Either I didn't get the exercise right or this is a bad idea, whatever
		if (c == ' ' || c == '\t') { 
			ungetch(c);
			ungetch(sign == -1 ? '-' : '+');
		}
	}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = *pn * 10 + (c - '0');

	*pn *= sign;

	if (c != EOF)
		ungetch(c);

	return c;
}

#define MAXBUF	10

int buflen = 0;
int buf[MAXBUF];

int getch(void) {
	return buflen ? buf[--buflen] : getchar();
}

void ungetch(int c) {
	if (buflen >= MAXBUF) {
		printf("ungetch: buffer is full\n");
	} else {
		buf[buflen++] = c;
	}
}
