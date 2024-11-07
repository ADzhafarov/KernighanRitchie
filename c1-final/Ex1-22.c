#include <stdio.h>

#define BUFLEN	10
#define IN		1
#define OUT		0

void printbuf(char buf[], int len);
void shiftbuf(char buf[], int shift);

int main(void) {
	int c, len, state, last_edge;
	char buf[BUFLEN];

	state = OUT;
	last_edge = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			printbuf(buf, len);
			printf("\n");
			len = 0;
			state = OUT;
			last_edge = 0;
		} else {
			if (c == ' ' || c == '\t') {
				if (state == IN)
					last_edge = len;
				state = OUT;
			} else {
				state = IN;
			}

			buf[len] = c;
			++len;

			if (len == BUFLEN) {
				if (last_edge > 0) {
					printbuf(buf, last_edge);
					printf("\n");
					shiftbuf(buf, last_edge);
					len = BUFLEN - last_edge;
					last_edge = 0;
				} else {
					printbuf(buf, BUFLEN);
					printf("~\n");
					len = 0;
				}
			}

		}
	}
}

void printbuf(char buf[], int len) {
	for (int i = 0; i < len; i++)
		printf("%c", buf[i]);
}

void shiftbuf(char buf[], int shift) {
	for (int i = 0; i < BUFLEN - shift; ++i)
		buf[i] = buf[i + shift];
}

