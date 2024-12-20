#include <stdio.h>

#define MAXLINE 1000

int max;
char line[MAXLINE];
char longest[MAXLINE];

int get_line(void);
void copy(void);

int main(void) {
	int len, c;
	extern int max;
	extern char longest[];

	max = 0;
	while ((len = get_line()) > 0) {
		if (line[len - 1] != '\n'){
			while ((c = getchar()) != EOF && c != '\n')
				++len;
			if (c == '\n')
				++len;
		}
		if (len > max) {
			max = len;
			copy();
		}
	}
	if (max > 0)
		printf("%d: %s", max, longest);
	return 0;
}

int get_line() {
	int c, i;
	extern char line[];

	for (i=0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n'){
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void copy() {
	int i;
	extern char line[], longest[];

	i = 0;
	while ((longest[i] = line[i]) != '\0')
		++i;
}








