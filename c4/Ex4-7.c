#include <stdio.h>
#include <string.h>

#define MAXWORD		10

int getch(void);
void ungetch(int c);
void ungets(char s[]);

int main(void) {
	int c, i;
	char s[MAXWORD];

	i = 0;
	while ((c = getch()) != EOF && c != '\n' && i < MAXWORD - 1) {
		s[i++] = c;
	}

	s[i] = '\0';

	printf("%s\n", s);

	ungetch('\n');
	ungets(s);

	i = 0;
	while ((c = getch()) != EOF && c != '\n' && i < MAXWORD - 1) {
		s[i++] = c;
	}

	s[i] = '\0';

	printf("%s\n", s);
}

#define BUFSIZE		100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[]) {
	int l = strlen(s);

	if (l > BUFSIZE - bufp)
		printf("ungets: too many characters\n");
	else
		while (l >= 0)
			ungetch(s[l--]);
}
