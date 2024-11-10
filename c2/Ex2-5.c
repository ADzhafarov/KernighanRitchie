#include <stdio.h>

int any(char s1[], char s2[]);

int main(void) {
	char s1[] = "kashdfgkljhqiueroyghouieajhrgklqjhgekltjqhekljtghwkljerhlqkjhgwreqk";
	char s2[] = "1234567890";

	printf("%d\n", any(s1, s2));
}

int contains(char s[], char c);

int any(char s1[], char s2[]) {
	int i, j;
	char c;

	i = j = 0;
	while (s1[i] != '\0') {
		c = s1[i];
		if (contains(s2, c)) {
			return i;
		}
		i++;
	}
	return -1;
}

int contains(char s[], char c) {
	int i = 0;
	while (s[i] != '\0')
		if (s[i++] == c)
			return 1;
	return 0;
}
