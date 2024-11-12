#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main(void) {
	printf("%f\n", atof("123"));
	printf("%.2f\n", atof("123.43"));
	printf("%.5f\n", atof("123.43e-3"));
	printf("%f\n", atof("123e+5"));
	printf("%f\n", atof("123e5"));
}

double atof(char s[]) {
	double val, power;
	int i, sign;

	int exp;
	float exp_multiplier;

	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = val * 10.0 + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = val * 10.0 + (s[i] - '0');
		power *= 10;
	}

	val = sign * val / power;

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		exp_multiplier = (s[i] == '-') ? 0.1 : 10.;
	}

	if (s[i] == '-' || s[i] == '+')
		i++;
	for (exp = 0; isdigit(s[i]); i++)
		exp = exp * 10 + (s[i] - '0');

	for (i = 0; i < exp; i++) {
		val *= exp_multiplier;
	}

	return val;
}
