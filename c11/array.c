/*
 * Horrible things to do with arrays.
 * OR Lessons in array indexing.
 */
#include <stdio.h>

int main( void )
{
	int i, a[10];

	for (i = 0; i < 10; i++)
		a[i] = i + 10 * i + 100 * i;

	/* transitive property of array indexing */
	for (i = 0; i < 10; i++) {
		printf("a[%d] = %d\t", i, a[i]);
		printf("*(a + i) = %d\t", *(a + i));
		printf("*(i + a) = %d\t", *(i + a));
		printf("i[a] = %d\n", i[a]);
	}

	return 0;
}

