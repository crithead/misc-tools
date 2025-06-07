/*
 * sizeof.c
 * Various experiments with the sizeof operator.
 */
#include <stdio.h>
#include <string.h>

static void types(void)
{
	printf("--- %s\n", "types");
	printf("sizeof(char)            %4d\n", (int)sizeof(char));
	printf("sizeof(short int)       %4d\n", (int)sizeof(short int));
	printf("sizeof(int)             %4d\n", (int)sizeof(int));
	printf("sizeof(long int)        %4d\n", (int)sizeof(long int));
	printf("sizeof(long long int)   %4d\n", (int)sizeof(long long int));
	printf("sizeof(float)           %4d\n", (int)sizeof(float));
	printf("sizeof(double)          %4d\n", (int)sizeof(double));
	printf("sizeof(long double)     %4d\n", (int)sizeof(long double));
}

static const char *STRING1 = "the first thing that comes along";
static const char STRING2[] = "another thing that's coming";

static void array(void)
{
	int x;
	printf("--- %s\n", "array");
	x = sizeof(STRING1);
	printf("sizeof(STRING1)  %4d\n", x);
	x = sizeof(*STRING1);
	printf("sizeof(*STRING1) %4d\n", x);
	x = sizeof(&STRING1);
	printf("sizeof(&STRING1) %4d\n", x);
	x = sizeof(STRING2);
	printf("sizeof(STRING2)  %4d\n", x);
	x = sizeof(&STRING2);
	printf("sizeof(&STRING2) %4d\n", x);
}


/* ************************************************************************ */
int main(int argc, char **argv)
{
	types();
	array();
	return 0;
}
