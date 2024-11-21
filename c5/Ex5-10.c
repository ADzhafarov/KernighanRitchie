#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP		100

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

int getop(char []);
void push(double);
double pop(void);

double variables[26];
double last;

int main(int argc, char *argv[]) {
	int type;
	double op, op2;

	while (--argc > 0) {
		type = getop(*++argv);
		switch (type) {
		case NUMBER:
			push(atof(*argv));
			break;
		case VARIABLE:
			if (**argv == '$')
				push(last);
			else
				push(variables[**argv - '0']);
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
			printf("error: unknown command %s\n", *argv);
			break;
		}
	}
	op = pop();
	printf("\t%.8g\n", op);
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

void getword(char s[], int maxlen);

int getop(char s[]) {
	int i;

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

void getword(char s[], int maxlen) {

	static int buf = 0;

	int i, c;

	i = 0;
	while ((c = (buf ? buf : getchar())) == ' ' || c == '\t')
		buf = 0;
	buf = 0;
	s[i++] = c;

	if (s[0] == '\n') {
		s[1] = '\0';
		return;
	}

	while ((c = (buf ? buf : getchar())) != ' ' && c != '\t' && c != '\n' && c != EOF && i < maxlen - 1) {
		s[i++] = c;
		buf = 0;
	}


	if (c == '\n' || c == EOF) {
		if (buf)
			printf("ungetch: too many characters\n");
		else {
			buf = c;
		}
	}

	s[i] = '\0';
}
