#include <assert.h>

/*
 * Mask with least significant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n)
{
	return (unsigned) ~0 >> ((sizeof(int) << 3) - n);
}

int main(int argc, char const *argv[])
{
	assert(lower_one_mask(6) == 0x3F);
	assert(lower_one_mask(17) == 0x1FFFF);
	assert(lower_one_mask(32) == 0xFFFFFFFF);
	return 0;
}
