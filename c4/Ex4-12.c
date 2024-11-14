#include <stdio.h>

#define MAXLEN		100

int itoa(int n, char s[], int start);

int main(void) { 
	char s[MAXLEN];

	itoa(123481, s, 0);
	printf("%s\n", s);
	itoa(3212, s, 0);
	printf("%s\n", s);
	itoa(-1231, s, 0);
	printf("%s\n", s);
	itoa(0, s, 0);
	printf("%s\n", s);
}

int itoa(int n, char s[], int level) {
	int pos = 0;
	
	if (n < 0) {
		s[0] = '-';
		return itoa(-n, s+1, 0) + 1;
	}

	if (n / 10)
		pos = itoa(n / 10, s, level + 1);
	
	s[pos] = n % 10 + '0';

	if (level == 0)
		s[pos + 1] = '\0';
	return pos + 1;
}
