#include <stdio.h>

/* The following code does not run properly on some machines */
int bad_int_size_is_32()
{
	/* Set most significant bit (msb) of 32-bit machine */
	int set_msb = 1 << 31;
	/* Shift past msb of 32-bit word */
	int beyond_msb = 1 << 32;
	// warning: left shift count >= width of type
	/* set_msb is nonzero when word size >= 32
	   beyond_msb is zero when word size <= 32 */
	return set_msb && !beyond_msb;
}

/* The following code runs properly on machines with word size >= 16 */
int int_size_is_32()
{
	int set_msb = 1 << 15;
	int beyond_msb;
	set_msb <<= 15;
	set_msb <<= 1;
	beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

int main(int argc, char const *argv[])
{
	if (int_size_is_32())
		printf("This is a 32-bit machine.\n");
	else
		printf("This is not a 32-bit machine.\n");
	return 0;
}
