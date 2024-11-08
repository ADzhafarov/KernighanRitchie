#include <stdio.h>

#define TABSTOP	4

int main(void) {
	int c, i, t;

	t = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			printf("%c", c);
			t = 0;
		} else if (c == '\t') {
			for (i = TABSTOP - t % TABSTOP; i > 0; --i)
				printf("%c", ' ');
			t = 0;
		} else {
			printf("%c", c);
			++t;
		}
	}
}
