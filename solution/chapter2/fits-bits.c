#include <assert.h>

/*
 * Return 1 when x can be represented as an n-bit, 2's-complement number;
 * 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits(int x, int n)
{
	return !(((x >> (n - 1)) + 1) >> 1);
}

int main(int argc, char* argv[])
{
	assert(!fits_bits(0xFF, 8));
	assert(!fits_bits(~0xFF, 8));
	assert(fits_bits(0b0010, 3));
	assert(!fits_bits(0b1010, 3));
	assert(!fits_bits(0b0110, 3));
	assert(fits_bits(~0b11, 3));
	assert(!fits_bits(~0b01000011, 3));
	assert(!fits_bits(~0b111, 3));
	return 0;
}
