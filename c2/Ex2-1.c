#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>


void calc_char(void);
void calc_short(void);
void calc_int(void);
void calc_long(void);
void calc_float(void);
void calc_double(void);

int main(void) {
	printf("\t     calculated\tconstant\n");
	calc_char();
	calc_short();
	calc_int();
	calc_long();
	calc_float();
	calc_double();
}


void calc_char(void) {
	signed char c, max, min;

	c = 1;
	while (c > 0) {
		c = c * 2;
	}
	min = c;
	max = c - 1;

	printf("signed char\n");
	printf("\tmin: %10d\t%8d\n", min, SCHAR_MIN);
	printf("\tmax: %10d\t%8d\n", max, SCHAR_MAX);

	unsigned char umin = 0;
	unsigned char umax = max;
	umax = umax * 2 + 1;

	printf("unsigned char\n");
	printf("\tmax: %10d\t%8d\n", umax, UCHAR_MAX);
}

void calc_short(void) {
	signed short c, max, min;

	c = 1;
	while (c > 0) {
		c = c * 2;
	}
	min = c;
	max = c - 1;

	printf("signed short\n");
	printf("\tmin: %10d\t%8d\n", min, SHRT_MIN);
	printf("\tmax: %10d\t%8d\n", max, SHRT_MAX);

	unsigned short umin = 0;
	unsigned short umax = max;
	umax = umax * 2 + 1;

	printf("unsigned short\n");
	printf("\tmax: %10d\t%8d\n", umax, USHRT_MAX);
}

void calc_int(void) {
	signed int c, max, min;

	c = 1;
	while (c > 0) {
		c = c * 2;
	}
	min = c;
	max = c - 1;

	printf("signed int\n");
	printf("\tmin: %10d\t%8d\n", min, INT_MIN);
	printf("\tmax: %10d\t%8d\n", max, INT_MAX);

	unsigned int umin = 0;
	unsigned int umax = max;
	umax = umax * 2 + 1;

	printf("unsigned int\n");
	printf("\tmax: %10u\t%8u\n", umax, UINT_MAX);
}

void calc_long(void) {
	signed long c, max, min;

	c = 1;
	while (c > 0) {
		c = c * 2;
	}
	min = c;
	max = c - 1;

	printf("signed long\n");
	printf("\tmin: %10ld\t%8ld\n", min, LONG_MIN);
	printf("\tmax: %10ld\t%8ld\n", max, LONG_MAX);

	unsigned long umin = 0;
	unsigned long umax = max;
	umax = umax * 2 + 1;

	printf("unsigned long\n");
	printf("\tmax: %10lu\t%8lu\n", umax, ULONG_MAX);
}

void calc_float(void) {
	float f, prev_f, max, min, alpha;

	f = 1.;
	prev_f = 0.;
	alpha = 1.;

	while (prev_f < f) {
		prev_f = f;
		while (isinf(f + f * alpha))
			alpha = alpha * 0.5;
		f = f + f * alpha;
	}

	printf("Float max:\n");
	printf("Calculated: %f\nFrom const: %f\n", f, FLT_MAX);

	f = 1.;
	prev_f = 2.;
	alpha = .5;

	while (prev_f > f) {
		prev_f = f;
		while (f - f * alpha <= 0)
			alpha = alpha * 0.5;
		f = f - f * alpha;
	}

	printf("Float min:\n");
	printf("Calculated: %.1000f\nFrom const: %.1000f\n", f, FLT_TRUE_MIN);
}

void calc_double(void) {
	double f, prev_f, max, min, alpha;

	f = 1.;
	prev_f = 0.;
	alpha = 1.;

	while (prev_f < f) {
		prev_f = f;
		while (isinf(f + f * alpha))
			alpha = alpha * 0.5;
		f = f + f * alpha;
	}

	printf("Double:\n");
	printf("Calculated: %f\nFrom const: %f\n", f, DBL_MAX);

	f = 1.;
	prev_f = 2.;
	alpha = .5;

	while (prev_f > f) {
		prev_f = f;
		while (f - f * alpha <= 0.)
			alpha = alpha * 0.5;
		f = f - f * alpha;
	}

	printf("Double min:\n");
	printf("Calculated: %.2000f\nFrom const: %.2000f\n", f, DBL_TRUE_MIN);
}

