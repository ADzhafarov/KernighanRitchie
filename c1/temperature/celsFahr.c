#include <stdio.h>

int main(void) {
	float lower, upper;
	float fahr, cels, step;

	lower = -17.8;
	step = 20. * (5./9.);
	upper = 150;


	printf("Celsius\tFahrenheit\n");
	cels = lower;
	while (cels <= upper) {
		fahr = (9./5.) * cels + 32.;
		printf("%7.1f\t%10.1f\n", cels, fahr);
		cels += step;
	}
}
