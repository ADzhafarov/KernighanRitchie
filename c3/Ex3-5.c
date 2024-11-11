#include <stdio.h>
#include <string.h>

#define MAXLEN		1000

void itob(int n, char s[], int b);

int main(void) {
	char s[1000];

	itob(255, s, 16);
	printf("%s\n", s);

	itob(7, s, 2);
	printf("%s\n", s);

	itob(238, s, 10);
	printf("%s\n", s);
}

void reverse(char s[]);

void itob(int n, char s[], int b) {
	int r;
	int i = 0;
	int sign = n;

	do {
		r = n % b;
		switch (r) {
			case 0: case 1: case 2: case 3: case 4:
			case 5: case 6: case 7: case 8: case 9:
				s[i++] = r + '0';
				break;
			case 10: case 11: case 12:
			case 13: case 14: case 15:
				s[i++] = r - 10 + 'A';
				break;
		}
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	
	s[i] = '\0';

	reverse(s);
}


void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) 
		c = s[i], s[i] = s[j], s[j] = c;
}
