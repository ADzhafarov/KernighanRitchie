#include <stdio.h>

#define LOWER  0
#define UPPER  300
#define STEP   20


float conversion(int fahr);

int main(void) {
	for (int fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP) {
		printf("%3d\t%6.1f\n", fahr, conversion(fahr));
	}
}

float conversion(int fahr) {
	return (5./9.) * (fahr - 32);
}
