#include <linux/limits.h>
#include <stdio.h>

#define MAXNEST			20

// State constants
#define DEFAULT			0
#define IN_SQUOTES		1
#define IN_DQUOTES		2
#define IN_COMMENT		3
#define INLINE_COMMENT	4

#define PARENTHESES		0
#define BRACKETS		1
#define BRACES			2

int validate(void);

int main(void) {
	int result;

	result = validate();
	
	if (result == 0)
		printf("Valid syntax\n");
	else if (result == 1)
		printf("Valid syntax\n");

}

int matching_open(int c);

int validate(void) {
	int c, next, prev, state, depth, backslashes;
	int enclosures[MAXNEST];

	backslashes = 0;
	state = DEFAULT;
	prev = -1;
	while ((c = getchar()) != EOF) {
		printf("%d", state);
		if (state == DEFAULT) {
			if (c == '(' || c == '[' || c == '{') {
				enclosures[depth] = c;
				++depth;
			} else if (c == ')' || c == ']' || c == '}') {
				if (depth == 0 || enclosures[depth-1] != matching_open(c)) {
					return 1;
				}
				--depth;
			} else if (c == '\'')
				state = IN_SQUOTES;
			else if (c == '\"')
				state = IN_DQUOTES;
			else if (c == '/') {
				next = getchar();
				if (next == EOF)
					return 1; // I guess no program can end with a slash? 0_0
				else if (next == '/')
					state = INLINE_COMMENT;
				else if (next == '*')
					state = IN_COMMENT;
			}
		} else if (state == IN_SQUOTES || state == IN_DQUOTES) {
			if (c == '\\')
				++backslashes;
			else {
				if (((c == '\'' && state == IN_SQUOTES) || (c == '\"' && state == IN_DQUOTES)) && backslashes % 2 == 0)
					state = DEFAULT;
				backslashes = 0;
			}
		} else if (state == IN_COMMENT) {
			if (c == '*' && (next = getchar()) == '/')
				state = DEFAULT;
		} else if (state == INLINE_COMMENT) {
			if (c == '\n') {
				state = DEFAULT;
			}
		}

		prev = c;
	}
	
	if (depth > 0 || state != DEFAULT)
		return 1;

	return 0;
}


int matching_open(int c) {
	if (c == ')')
		return '(';
	if (c == ']')
		return '[';
	if (c == '}')
		return '{';
	return -1;
}
