#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {
	printf("%d\n", day_of_year(2024, 8, 13));
	int day, month;
	month_day(2024, 226, &month, &day);
	printf("%d %d\n", day, month);

	printf("%d\n", day_of_year(2024, 13, 2));
	printf("%d\n", day_of_year(2024, -1, 2));
	printf("%d\n", day_of_year(2024, 11, 32));
	printf("%d\n", day_of_year(2024, 11, -1));

	printf("%d\n", month_day(2024, 366, &month, &day));
	printf("%d %d\n", day, month);
	printf("%d\n", month_day(2025, 366, &month, &day));
	printf("%d %d\n", day, month);

}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

#define DAYS	365

int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (yearday <= 0 || yearday > DAYS + leap)
		return -1;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return 0;
}


