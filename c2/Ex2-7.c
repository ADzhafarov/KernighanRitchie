#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void) {
	printf("%u\n", invert(4U, 3, 2));
	printf("%u\n", invert(64U, 4, 2));
}

unsigned invert(unsigned x, int p, int n) {
	return x ^ (~(~0 << n) << (p - n));
}
