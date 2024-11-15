#include <limits.h>
#include <stdio.h>

#define MAXLEN		100

void itoa(char *s, int n);

int main(void) {
	char s[MAXLEN];

	itoa(s, 1234);
	printf("%s\n", s);
	itoa(s, -1234);
	printf("%s\n", s);
	itoa(s, 0);
	printf("%s\n", s);
	itoa(s, INT_MIN);
	printf("%d\t\t%s\n", INT_MIN, s);
}

void reverse(char *s);

void itoa(char *s, int n) {
	int overflow = 0;
	int sign = n;

	char *p = s;

	if (n < 0) {
		n = -n;
		if (n < 0) {
			overflow = 1;
			n -= 1;
		}
	}

	do {
		*s++ = n % 10 + '0';
		n /= 10;
	} while (n > 0);

	if (sign < 0)
		*s++ = '-';

	*s = '\0';

	if (overflow)
		(*p)++;

	reverse(p);
}

void reverse(char *s) {
	char tmp;
	char *p = s;
	
	while (*s != '\0')
		s++;

	s--;

	while (s - p > 0) {
		tmp = *s, *s = *p, *p = tmp;
		s--, p++;
	}
}
