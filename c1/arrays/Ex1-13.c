#include <stdio.h>

#define IN	1
#define OUT	0

int main(void) {
	int i, c, l, state;
	int lengths[100];

	for (i = 0; i < 100; i++)
		lengths[i] = 0;

	state = OUT;
	l = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				++lengths[l];
				state = OUT;
			}
			l = 0;
		} else {
			++l;
			state = IN;
		}
	}

	for (i = 0; i < 100; i++){
		int j;
		if (lengths[i] != 0){
			printf("%d |", i);
			for (j = 0; j < lengths[i]; j++){
				printf("#");
			}
			printf("\n");
		}
	}

}
