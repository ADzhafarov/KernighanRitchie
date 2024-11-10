#include <stdio.h>

int htoi(char hex[]);

int main(void) {
	char hex[] = "0xFAA921C";

	printf("%d\n", htoi(hex));
}

int htoi(char hex[]) {

	int i;
	
	int res = 0;

	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	else
		i = 0;

	while (hex[i] != '\0') {
		res *= 16;
		if ('0' <= hex[i] && hex[i] <= '9') {
			res += hex[i] - '0';
		} else if ('a' <= hex[i] && hex[i] <= 'f') {
			res += 10 + hex[i] - 'a';
		} else if ('A' <= hex[i] && hex[i] <= 'F') {
		res += 10 + hex[i] - 'A';
		} else {
			return -1;
		}
		++i;
	}

	return res;
}
