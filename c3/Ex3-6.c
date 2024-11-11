#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLEN		1000

void itoa(int n, char s[], int m_width);

int main(void) {

	char s[MAXLEN];
	itoa(1238, s, 10);
	printf("%s\n", s);
}

void reverse(char s[]);

void itoa(int n, char s[], int m_width) {
	int i, sign, overflow_flg;

	overflow_flg = 0;
	if ((sign = n) < 0) {
		n = -n;
		if (n < 0) {
			n++;
			n = -n;
			overflow_flg = 1;
		}
	}

	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	
	if (sign < 0)
		s[i++] = '-';
	while(i < m_width)
		s[i++] = ' ';
	s[i] = '\0';
	if (overflow_flg)
		s[0]++; // INT_MIN is always -2^k, so s[0] is never 9 at that point;

	reverse(s);
}

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) 
		c = s[i], s[i] = s[j], s[j] = c;
}
