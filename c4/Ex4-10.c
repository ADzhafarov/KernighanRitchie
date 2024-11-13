#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP		100
#define MAXLINE		1000

enum operations {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	MOD = '%',
	NUMBER = 11,
	SET_VAR,
	VARIABLE,
	PRINT,
	DUPLICATE,
	SWAP,
	SIN,
	COS,
	EXP,
	POW,
	UNDEFINED,
};

int getop(char[], char []);
void push(double);
double pop(void);
int get_line(char s[], int lim);

double variables[26];
double last;

int main(void) {
	int type, len;
	double op, op2;
	char line[MAXLINE];
	char s[MAXOP];

	while ((len = get_line(line, MAXLINE)) > 0) {
		while ((type = getop(line, s)) != EOF) {
			switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case SET_VAR:
				variables[s[0] - '0'] = atof(s+2);
				break;
			case VARIABLE:
				if (s[0] == '$')
					push(last);
				else
					push(variables[s[0] - '0']);
				break;
			case ADD:
				push(pop() + pop());
				break;
			case MUL:
				push(pop() * pop());
				break;
			case SUB:
				op2 = pop();
				push(pop() - op2);
				break;
			case DIV:
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero division\n");
				break;
			case MOD:
				op2 = pop();
				if (op2 != 0.0)
					push((int)pop() % (int)op2);
				else
					printf("error: zero division\n");
				break;
			case PRINT:
				op = pop();
				printf("\t%.8g\n", op);
				push(op);
				break;
			case DUPLICATE:
				op = pop();
				push(op);
				push(op);
				break;
			case SWAP:
				op = pop();
				op2 = pop();
				push(op);
				push(op2);
				break;
			case SIN:
				push(sin(pop()));
				break;
			case COS:
				push(cos(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case '\n':
				op = pop();
				printf("\t%.8g\n", op);
				last = op;
				break;
			default:
				printf("error: unknown command %s|\n", s);
				break;
			}
		}
	}
	return 0;
}

#define MAXVAL		100

int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else
		printf("error: the stack is full, can't push %g\n", f);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: the stack is empty\n");
		return 0.0;
	}
}

int getword(char line[], char s[], int maxlen);

int getop(char line[], char s[]) {
	int i;

	if (getword(line, s, MAXOP) == 0)
		return EOF;

	if (s[1] == '\0' && ('a' <= s[0] && s[0] <= 'z') || s[0] == '$')
		return VARIABLE;

	if (s[1] == '\0' && !isdigit(s[0]))
		return s[0];

	if ('a' <= s[0] && s[0] <= 'z' && s[1] == '=') {
		i = 2;
		while (isdigit(s[++i]))
			;
		if (s[i] == '.')
			while (isdigit(s[++i]))
				;
		s[i] = '\0';
		return SET_VAR;
	}

	if (isdigit(s[0]) || s[0] == '.' || s[0] == '-') {
		i = 0;
		while (isdigit(s[++i]))
			;

		if (s[i] == '.')
			while (isdigit(s[++i]))
				;
		s[i] = '\0';

		return NUMBER;
	}

	if (strcmp(s, "print") == 0)
		return PRINT;
	
	if (strcmp(s, "duplicate") == 0)
		return DUPLICATE;

	if (strcmp(s, "swap") == 0)
		return SWAP;

	if (strcmp(s, "sin") == 0)
		return SIN;

	if (strcmp(s, "cos") == 0)
		return COS;

	if (strcmp(s, "exp") == 0)
		return EXP;

	if (strcmp(s, "pow") == 0)
		return POW;

	return UNDEFINED;
}

int getword(char line[], char s[], int maxlen) {
	int i, j, c;

	i = 0;
	for (j = strlen(line) - 1; j >= 0 && ((c = line[j]) == ' ' || c == '\t'); j--)
		;
	

	if (j < 0) {
		s[0] = '\0';
		return 0;
	}

	while (j >= 0 && (s[i] = line[j--]) != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;

	if (s[i] == '\n') {
		if (i == 0)
			s[i++] = '\n';
		else
			j++;
	}


	s[i] = '\0';
	line[j + 1] = '\0';

	return i;
}

void reverse(char s[]);

int get_line(char s[], int lim) {
	int c, i;

	for (i=0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	
	s[i] = '\0';
	reverse(s);
	return i;
}

void reverse(char s[]) {
	int tmp, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		tmp = s[i], s[i] = s[j], s[j] = tmp;
}
