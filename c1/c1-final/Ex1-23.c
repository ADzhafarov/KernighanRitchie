#include <stdio.h>

/* code state */
#define DEFAULT			0
#define IN_STRING		1 
#define	IN_COMMENT		2
#define INLINE_COMMENT	3

int main(void) {
	int c, next, state, backslashes;

	state = DEFAULT;

	backslashes = 0;
	while ((c = getchar()) != EOF) {
		if (state == DEFAULT) {
			if (c == '"') {
				state = IN_STRING;
				printf("%c", c);
			}
			else if (c == '/') {
				if ((next = getchar()) != '*') {
					if (next == '/') {
						state = INLINE_COMMENT;
					} else {
						printf("%c", c);
						if (next != EOF)
							printf("%c", next);
					}
				} else {
					state = IN_COMMENT;
				}
			} else {
				printf("%c", c);
			}
		} else if (state == IN_STRING) {
			if (c == '\\')
				++backslashes;
			else
				backslashes = 0;
			if (c == '"' && backslashes % 2 == 0)
				state = DEFAULT;
			printf("%c", c);
		} else if (state == IN_COMMENT) {
			if (c == '*' && (next = getchar()) == '/')
				state = DEFAULT;
		} else if (state == INLINE_COMMENT) {
			if (c == '\n') {
				printf("%c", c);
				state = DEFAULT;
			}
		}
	}

	printf("Programm /*decommenter*/ finished it's work!"); // A comment to get rid of :P

}

