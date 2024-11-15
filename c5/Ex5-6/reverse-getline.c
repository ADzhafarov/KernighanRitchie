#include <stdio.h>

#define MAXLINE		1000

int get_line(char *s, int lim);
void reverse(char *s);


int main(void) {
	char line[MAXLINE];
	int len;
	while ((len = get_line(line, MAXLINE)) > 0) {
		reverse(line);
		printf("%s", line);
	}
}

int get_line(char *s, int lim) {
	int c, len;

	len = 0;
	while (lim-- > 0 && (*s = getchar()) != '\n' && *s != EOF)
		s++, len++;

	if (*s == '\n')
		s++, len++;

	*s = '\0';

	return len;
}

void reverse(char *s) {
	char tmp;
	char *p = s;
	
	while (*s != '\0' && *s != '\n')
		s++;

	s--;

	while (s - p > 0) {
		tmp = *s, *s = *p, *p = tmp;
		s--, p++;
	}
}
