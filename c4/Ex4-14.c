#include <stdio.h>

#define swap(t, x, y)	{ t swap_tmp = x; x = y; y = swap_tmp; }

int main(void) {
	int a = 42, b = 69;
	float x = 3.14, y = 2.72;

	swap(int, a, b);
	swap(float, x, y);

	printf("\t\t%d\t%d\n", a, b);
	printf("\t\t%f\t%f\n", x, y);
}
