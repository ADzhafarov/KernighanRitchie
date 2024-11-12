#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]);

int main(void) {

	printf("%d\n", strindex("aaaaaaaa", "a"));
	printf("%d\n", strindex("aaaaaaaa", "aa"));
	printf("%d\n", strindex("aaaaaaaa", "aaaaaaaa"));
	printf("%d\n", strindex("aaaaaaaa", "aaaaaaaaa"));

}

int strindex(char s[], char t[]) {
	int i, j, k;

	for (i = strlen(s) - 1; i >= 0; i--) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}
