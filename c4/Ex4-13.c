#include <stdio.h>
#include <string.h>

void reverse(char s[], int start, int end);

int main(void) {
	char s[] = "Hello, world!";
	printf("%s\n", s);
	reverse(s, 0, strlen(s) - 1);
	printf("%s\n", s);
}

void reverse(char s[], int start, int end) {
	int tmp;

	if (start >= end)
		return;

	tmp = s[start];
	s[start] = s[end];
	s[end] = tmp;

	reverse(s, start + 1, end - 1);
}
