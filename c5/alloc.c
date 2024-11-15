#include <stdio.h>

char *alloc(int n);
void afree(char *p);

int main(void) {
	char *arr = alloc(14);
	arr = "Hello, world!";
	for (int i = 0; i < 14; i++) {
		printf("%c", arr[i]);
	}

}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

void afree(char *p) {
	if (p > allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
