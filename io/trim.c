#include <stdio.h>

int main(void) {
	int blank;
	int c;

	blank = 0;
	while ((c = getchar()) != EOF) {
		if (!(c == ' ' && blank)) {
			putchar(c);
		}
		blank = c == ' ';
	}
}
