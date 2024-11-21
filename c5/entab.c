#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS		20

int next_tabstop(int pos, int *tabstops);

int main(int argc, char *argv[]) {
	int c, i, t;
	int tabstop;
	int tabstops[MAXSTOPS];

	int start, inc;
	if (argc == 3 && **(argv + 1) == '-' && **(argv + 2) == '+') {
		start = atoi(*(argv + 1) + 1);
		inc = atoi(*(argv + 2) + 1);
		for (i = 0; i < MAXSTOPS; i++) {
			tabstops[i] = start + i * inc;
		}
	} else
		for (i = 0; i < MAXSTOPS; i++)
			tabstops[i] = --argc > 0 ? atoi(*++argv) : tabstops[i-1] + 4;

	t = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			printf("%c", c);
			t = 0;
		} else if (c == '\t') {
			tabstop = next_tabstop(t, tabstops);
			for (i = tabstop - t; i > 0; --i) {
				t++;
				printf("%c", ' ');
			}
		} else {
			printf("%c", c);
			++t;
		}
	}
}

int next_tabstop(int pos, int *tabstops) {
	while (*tabstops++ <= pos)
		;

	return *--tabstops;
}
