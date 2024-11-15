#include <stdio.h>

#define MAXTO		1000

void strncpy_(char *from, char*to, int n);
void strncat_(char *from, char*to, int n);
int strncmp_(char *s, char*t, int n);

int main(void) {
	char t[MAXTO];
	char s[] = "Hello, world!";
	
	strncpy_(s, t, 13);
	printf("%s\n", t);
	strncat_(s, t, 7);
	printf("%s\n", t);
	strncat_(s, t, 7);
	printf("%s\n", t);
	printf("%d\n", strncmp_(s, t, 13));
	*(s + 5) = '.';
	printf("%d\n", strncmp_(s, t, 5));
	printf("%d\n", strncmp_(s, t, 6));

}

void strncpy_(char *from, char*to, int n) {
	while (n-- > 0 && (*to++ = *from++))
		;
	if (*(to - 1) != '\0')
		*to = '\0';
}

void strncat_(char *from, char*to, int n) {
	while (*to++)
		;

	to--;

	while (n-- > 0 && (*to++ = *from++))
		;

	if (*(to - 1) != '\0')
		*to = '\0';
}

int strncmp_(char *s, char *t, int n) {
	if (n == 0)
		return 0;
	while (n-- > 0 && (*s++ == *t++))
		;
	return *(s - 1) - *(t - 1);
}
