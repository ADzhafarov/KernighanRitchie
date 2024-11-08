#include <stdio.h>

#define MAXLINELEN	10

void reverse(char s[], int len);
int get_line(char line[], int maxline);

int main(void) {
	int c, i, len;
	char line[MAXLINELEN];

	while ((len = get_line(line, MAXLINELEN)) > 0) {
		if (line[len-1] == '\n') {
			reverse(line, len-1);
			for (i = 0; i < len - 1; ++i)
				printf("%c", line[i]);
			printf("%c", '\n');
		} else {
			while ((c = getchar()) != EOF && c != '\n')
				;
			reverse(line, len);
			for (i = 0; i < len; ++i)
				printf("%c", line[i]);
			printf("%c", '\n');
		}
	}
}

void reverse(char s[], int len) {
	int c, i;

	for (i = 0; i < (len - 1) / 2; ++i) {
		c = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = c;
	}
}

int get_line(char s[], int lim) {
	int c, i;

	for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
