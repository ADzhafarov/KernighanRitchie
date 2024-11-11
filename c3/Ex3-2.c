#include <stdio.h>

#define MAXSIZE		100

void escape(char s[], char t[]);
void revert(char t[], char u[]);

int main(void) {
	char s[] = "a\nb\tc\rd";
	char t[MAXSIZE];
	char u[MAXSIZE];
	printf("%s\n", s);
	escape(s, t);
	printf("%s\n", t);
	revert(t, u);
	printf("%s\n", u);
}

void escape(char s[], char t[]) {
	int i, j;
	for (i = j = 0; s[i] != '\0'; i++) {
		switch (s[i]) {
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\r':
				t[j++] = '\\';
				t[j++] = 'r';
			case '\\':
				t[j++] = '\\';
				t[j++] = '\\';
			default:
				t[j++] = s[i];
				break;
		}
	}
	t[j] = '\0';
}

void revert(char t[], char u[]) {
	int i, j;
	for (i = j = 0; t[i] != '\0'; i++) {
		if (t[i] == '\\') {
			switch (t[++i]) {
				case 't':
					u[j++] = '\t';
					break;
				case 'n':
					u[j++] = '\n';
					break;
				case 'r':
					u[j++] = '\r';
					break;
				case '\\':
					u[j++] = '\\';
					break;
			}
		} else {
			u[j++] = t[i];
		}
	}
	u[j] = '\0';
}
