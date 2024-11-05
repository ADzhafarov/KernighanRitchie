#include <stdio.h>

int main(void) {
	int b, t, n;
	int c;

	b = 0;
	t = 0;
	n = 0;

	while ((c = getchar()) != EOF) {
		b += c == ' ';
		t += c == '\t';
		n += c == '\n';
	}

	printf("Blanks: %d\nTabs: %d\nNewlines: %d\n", b, t, n);
}
