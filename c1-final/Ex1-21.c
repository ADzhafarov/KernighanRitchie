#include <stdio.h>

#define TABSTOP		4
#define IN			1
#define OUT			0

int main(void) {
	int c, i, l, state, t;

	l = t = 0;
	state = OUT;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			++l;
			state = OUT;
		} else {
			if (state == OUT) {
				if (l == 1 || t % TABSTOP + l < TABSTOP) {
					for (i = 0; i < l; ++i)
						printf("%c", ' ');
					t += l;
				} else {
					l += t % TABSTOP;
					t -= t % TABSTOP;
					for (i = 0; i < l / TABSTOP; ++i)
						printf("%c", '\t');
					t += TABSTOP * (l / TABSTOP);
					for (i = 0; i < l % TABSTOP; ++i) 
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
