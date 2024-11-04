#include <stdio.h>

int main(void) {
	for (int fahr = 300; fahr >= 0; fahr = fahr - 20) {
		printf("%3d\t%6.1f\n", fahr, (5./9.) * (fahr - 32));
	}
}
