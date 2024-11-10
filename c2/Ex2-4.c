#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void) {
	char s1[] = "asdkhjf13478fh67i51543877fgy2hk1j5hasdxf6g1q4918fyh524iyjg";
	char s2[] = "abcdefghijklmnopqrstuvwxyz";
	squeeze(s1, s2);
	printf("%s\n", s1);
	
}

int contains(char s[], char c);

void squeeze(char s1[], char s2[]) {
	int i, j;
	char c;

	i = j = 0;
	while (s1[i] != '\0') {
		c = s1[i++];
		if (!contains(s2, c)) {
			s1[j++] = c;
		}
	}
	s1[j] = '\0';
}

int contains(char s[], char c) {
	int i = 0;
	while (s[i] != '\0')
		if (s[i++] == c)
			return 1;
	return 0;
}
