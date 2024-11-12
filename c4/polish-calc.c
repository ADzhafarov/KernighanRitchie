#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP		100
#define NUMBER		'0'

int getop(char []);
void push(double);
double pop(void);

int main(void) {
	int type;
	double op, op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero division\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((int)pop() % (int)op2);
			else
				printf("error: zero division\n");
			break;
		case 'p': /* print */
			op = pop();
			printf("\t%.8g\n", op);
			push(op);
			break;
		case 'd': /* duplicate */
	 		op = pop();
			push(op);
			push(op);
			break;
		case 's': /* swap */
			op = pop();
			op2 = pop();
			push(op);
			push(op2);
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
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

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;

	if (c == '-') {
		if ((c = getch()) == ' ' || c == '\t' || c == '\n' || c == EOF) {
			if (c == '\n')
				ungetch(c);
			return '-';
		}
		else ungetch(c);
	}

	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE		100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
