#include <stdio.h>

#define MIN_SIZE 80

int main(void) {
	int c, l, i;
	int prefix[MIN_SIZE];

	l = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			if (l < MIN_SIZE) {
				prefix[l] = c;
			} else if (l == MIN_SIZE) {
				for (i = 0; i < MIN_SIZE; i++)
					printf("%c", prefix[i]);
				printf("%c", c);
			} else {
				printf("%c", c);
			}
			++l;
		} else {
			if (l >= 80)
				printf("\n");
			l = 0;
		}
	}

}

