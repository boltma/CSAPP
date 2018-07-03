#include <assert.h>

/* Compute 3/4x and the code does not overflow */
int threefourths(int x)
{
	int remain = x & 3;
	int fourth = x >> 2;
	int w = sizeof(int) << 3;
	int bias = ((x >> (w - 1)) & 1) && remain;
	remain += remain << 1;
	remain >>= 2;
	fourth += fourth << 1;
	return fourth + remain + bias;
}

int main(int argc, char const *argv[])
{
	assert(threefourths(8) == 6);
	assert(threefourths(9) == 6);
	assert(threefourths(10) == 7);
	assert(threefourths(11) == 8);
	assert(threefourths(12) == 9);
	assert(threefourths(-8) == -6);
	assert(threefourths(-9) == -6);
	assert(threefourths(-10) == -7);
	assert(threefourths(-11) == -8);
	assert(threefourths(-12) == -9);
	return 0;
}
