#include <stdio.h>

int bitcount(unsigned x);

int main(void) {
	printf("%d\n", bitcount(1));
	printf("%d\n", bitcount(2));
	printf("%d\n", bitcount(3));
	printf("%d\n", bitcount(7));
	printf("%d\n", bitcount(128));
	printf("%d\n", bitcount(127));
}

int bitcount(unsigned x) {
	int b ;
	// Every (non-zero) number can be represented like this x..x10..0 where
	//		1) the amount of 0-s at the end is k >= 0
	//		2) x..x is arbitrary
	// After subtracting 1 this turns into x..x01..1 where
	//		1) the amount of 1-s at the end is k
	//		2) x..x is the same as before
	// Bitiwise 'and' turns this into x..x00..0, which is the initial number
	//	with rightmost 1-bit turned into 0.
	for (b = 0; x != 0; x &= x - 1)
		b++;
	return b;
}
