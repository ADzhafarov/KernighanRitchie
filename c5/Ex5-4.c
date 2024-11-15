#include <stdio.h>

int strend(char *s, char *t);

int main(void) {
	printf("%d\n", strend("Hello, world!", "world!"));
	printf("%d\n", strend("Hello, world!", "shmorld!"));
	printf("%d\n", strend("Hello, world!", "gorld!"));
}

int strend(char *s, char *t) {
	int sl = 0;
	int tl = 0;

	while (*s++)
		sl++;

	while (*t++)
		tl++;

	if (sl < tl)
		return 0;

	tl++;
	while (tl > 0 && *--s == *--t)
		tl--;

	if (tl == 0)
		return 1;

	return 0;
}
