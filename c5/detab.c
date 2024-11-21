#include <stdio.h>
#include <stdlib.h>

#define IN			1
#define OUT			0
#define MAXSTOPS	20

int next_tabstop(int pos, int *tabstops);

int main(int argc, char *argv[]) {
	int c, i, l, state, t;
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

	int next_t = 0;
	l = t = 0;
	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++l;
			state = OUT;
		} else {
			if (state == OUT) {
				if (l == 1 || next_tabstop(t, tabstops) == next_tabstop(t + l, tabstops)) {
					for (i = 0; i < l; ++i)
						printf("%c", ' ');
					t += l;
				} else {
					while ((next_t = next_tabstop(t, tabstops)) < next_tabstop(t + l, tabstops)) {
						l -= next_t - t;
						t = next_t;
						printf("%c", '\t');
					}
					for (i = 0; i < l; ++i) 
						printf("%c", ' ');
				}
				state = IN;
				l = 0;
			}

			if (c == '\n')
				t = 0;

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
