#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN	1000

void expand(char s1[], char s2[]);

int main(void) {
	char s[] = "a-z\nA-Z\n0-9\n-a-b-c-d-z-\1n";
	char t[MAXLEN];
	expand(s, t);
	printf("%s", t);
}


void expand(char s1[], char s2[]) {
	int i, j, c;

	for (i = j = 0; s1[i] != '\0'; i++) {
		if (i != 0 && i != strlen(s1) - 1 && s1[i] == '-') {
			if (
				('a' <= s1[i - 1] && s1[i - 1] < s1[i + 1] && s1[i + 1] <= 'z') ||
				('A' <= s1[i - 1] && s1[i - 1] < s1[i + 1] && s1[i + 1] <= 'Z') ||
				('0' <= s1[i - 1] && s1[i - 1] < s1[i + 1] && s1[i + 1] <= '9')
			)
				for (c = s1[i - 1] + 1; c < s1[i + 1]; c++)
					s2[j++] = c;
			else
				s2[j++] = '-';
		} else {
			s2[j++] = s1[i];
		}
	}
}
