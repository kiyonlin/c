#include <stdio.h>

int main(void)
{
	printf("Type int has a size of %zd bytes.\n", sizeof(int));
	printf("Type short has a size of %zd bytes.\n", sizeof(short));
	printf("Type unsigned has a size of %zd bytes.\n", sizeof(unsigned));
	printf("Type char has a size of %zd bytes.\n", sizeof(char));
	printf("Type long has a size of %zd bytes.\n", sizeof(long));
	printf("Type long long has a size of %zd bytes.\n", sizeof(long long));
	printf("Type double has a size of %zd bytes.\n", sizeof(double));
	printf("Type long double has a size of %zd bytes.\n", sizeof(long double));
	printf("Type float has a size of %zd bytes.\n", sizeof(float));

	int n=0;
	size_t intSize;
	intSize = sizeof(int);
	printf("n = %d, n has %zd bytes; all ints have %zd bytes.\n", n, sizeof n, intSize);
	return 0;
}