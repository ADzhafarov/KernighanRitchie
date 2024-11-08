#include <stdio.h>

int main(void) {
	int i, c;
	int freqs[128];

	for (i = 0; i < 127; i++)
		freqs[i] = 0;

	while ((c = getchar()) != EOF)
		++freqs[c];

	for (i = 0; i < 127; i++){
		int j;
		if (freqs[i] != 0){
			printf("%c |", i);
			for (j = 0; j < freqs[i]; j++){
				printf("#");
			}
			printf("\n");
		}
	}

}
