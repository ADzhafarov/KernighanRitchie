#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void) {
 
	unsigned x = 0; 
	unsigned y = 7;

	printf("%u\n", setbits(x, 3, 3, y));
	printf("%u\n", setbits(x, 6, 3, y));
	printf("%u\n", setbits(x, 9, 3, y));
	printf("%u\n", setbits(x, 12, 3, y));

}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned x_mask = ~(~(~0 << n) << (p - n));
	unsigned y_mask = (~(~0 << n) & y) << (p - n);
	x = x & x_mask;
	x = x | y_mask;
	return x;
}
