#include <stdio.h>

#define MAX_CONSECUTIVE_BLANKS 1000
#define IN	1
#define OUT	0

int main(void) {
	int c, i, state, l;
	int buffer[MAX_CONSECUTIVE_BLANKS];
	
	state = OUT;
	l = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			if (state == IN) {
				printf("\n");
			}
			state = OUT;
			l = 0;
		} else if (c == ' ' || c == '\t') {
			if (state == IN) {
				buffer[l] = c;
				++l;
			}
		} else {
			if (l > 0) {
				for (i = 0; i < l; ++i)
					printf("%c", buffer[i]);
				l = 0;
			}
			printf("%c", c);
			state = IN;
		}
	}
}
