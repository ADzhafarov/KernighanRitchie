#include <stdio.h>

void strcpy1(char *s, char *t) {
	int i = 0;

	while ((t[i] = s[i]) != '\0')
		i++;
}

void strcpy2(char *s, char *t) {
	while (*t++ = *s++)
		;
}

int main(void) {
	char *s = "Hello";
	char *t;

	strcpy2(s, t);
	printf("%s\n", t);
}
