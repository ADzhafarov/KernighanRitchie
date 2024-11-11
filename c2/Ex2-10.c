#include <stdio.h>

char lower(char c) {
	return ('A' <= c && c <= 'Z') ? c - ('A' - 'a') : c;
}

int main(void) {
	int i;
	char s[] = "HeLlO, WoRLd!\n";

	for (i = 0; s[i] != '\0'; i++) {
		printf("%c", (i == 0) ? s[i] : lower(s[i]));
	}
}
