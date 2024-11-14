#include <limits.h>
#include <stdio.h>

void printd(int n);

int main(void) {
	printd(128);
	printf("\n");
	printd(-128);
	printf("\n");
	printd(0);
	printf("\n");
	printd(INT_MIN);
	printf("\n");
}

void printd(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}
