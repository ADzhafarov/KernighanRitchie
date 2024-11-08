#include <stdio.h>

int main(void) {
	int c;
	while (1) {
		c = getchar();
		if (c != '\n') {
			printf("%d\n", c != EOF);
		}
	}
}
