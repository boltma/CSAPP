#include <assert.h>

/*
 * Generate mask indicating leftmost 1 in x.  Assume w=32.
 * For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return (x >> 1) + (x && 1);
}

int main(int argc, char const *argv[])
{
	assert(leftmost_one(0xFF00) == 0x8000);
	assert(leftmost_one(0x6600) == 0x4000);
	assert(leftmost_one(0x0) == 0x0);
	assert(leftmost_one(0x1) == 0x1);
	assert(leftmost_one(0x80000000) == 0x80000000);
	return 0;
}
