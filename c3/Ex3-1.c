#include <stdio.h>
#include <time.h>
#include <wchar.h>

#define LEN 2000000
#define TIMES 5000000

int bin_search(int array[], int len, int val);
int bin_search2(int array[], int len, int val);

int main(void) {
	int i, array[LEN];

	for (i = 0; i < LEN; i++)
		array[i] = i;

	clock_t t0 = clock();

	for (i = 0; i < TIMES; i++)
		bin_search(array, LEN, -1);

	clock_t t1 = clock();

	for (i = 0; i < TIMES; i++)
		bin_search2(array, LEN, -1);

	clock_t t2 = clock();

	printf("CLOCKS_PER_SEC:\t%lu\n", CLOCKS_PER_SEC);
	printf("bin_search() took %lu clocks and %.10f seconds\n", t1-t0, (t1-t0) / (float)CLOCKS_PER_SEC);
	printf("bin_search2() took %lu clocks and %.10f seconds\n", t2-t1, (t2-t1) / (float)CLOCKS_PER_SEC);
}

int bin_search(int array[], int len, int val) {
	int middle, left, right;
	left = 0;
	right = len - 1;
	while (left <= right) {
		middle = (right - left) / 2 + left;
		if (array[middle] < val) {
			left = middle + 1;
		} else if (array[middle] > val) {
			right = middle - 1;
		} else {
			return middle;
		}
	}
	return -1;
}

int bin_search2(int array[], int len, int val) {
	int middle, left, right;
	left = 0;
	right = len - 1;
	while (left < right) {
		middle = (right - left) / 2 + left;
		if (array[middle] < val) {
			left = middle + 1;
		} else {
			right = middle;
		}
	}

	if (array[left] == val) {
		return left;
	}

	return -1;
}
