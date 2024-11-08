#include <stdio.h>

int main(void) {
	int c, nl;

	nl = 0;
	while ((c = getchar()) != EOF) 
		nl += c == '\n';

	printf("%d\n", nl);
}
