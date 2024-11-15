#include <stdio.h>

void strca(char *s, char *t);

#define MAXLEN		1000

int main(void) {
	char s[MAXLEN] = "Hello, ";
	char *t = "World!";

	strca(s, t);
	printf("%s\n", s);
}

void strca(char *s, char *t) {
	while (*s++)
		;

	s--;

	while (*s++ = *t++)
		;
}
