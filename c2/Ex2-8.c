#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n); 

int main(void) {
	printf("%u\n", rightrot(3U, 1));
}

unsigned rightrot(unsigned x, int n) {
	int size = sizeof(int) * 8;
	return x >> (n % size) | x << (size - n % size);
}
