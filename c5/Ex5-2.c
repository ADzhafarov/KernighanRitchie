#include <ctype.h>
#include <stdio.h>

#define SIZE	100

int getfloat(float *pn);

int main(void) {
	int i, n;
	float array[SIZE];

	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;

	for (i = 0; i < n; i++)
		printf("%g\n", array[i]);
}

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
	int c, sign, pow;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '-' && c != '+') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
	}

	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = *pn * 10.0 + (c - '0');

	if (c == '.') {
		for (pow = 1.0; isdigit(c = getch()); pow *= 10.0)
			*pn = *pn * 10.0 + (c - '0');
		*pn /= pow;
	}

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
