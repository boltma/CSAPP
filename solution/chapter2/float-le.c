#include <assert.h>

unsigned f2u(float x)
{
	return *(unsigned *)&x;
}

/* Determine whether x is less than or equal to y. Assume x and y are both not NaN. +0 = -0. */
int float_le(float x, float y)
{
	unsigned ux = f2u(x);
	unsigned uy = f2u(y);

	/* Get the sign bits */
	unsigned sx = ux >> 31;
	unsigned sy = uy >> 31;

	/* Give an expression using only ux, uy, sx, and sy */
	return (sx && !sy) ||
	       (ux == 0 && uy == 0x80000000u) ||
	       (sx && sy && ux >= uy) ||
	       (!sx && !sy && ux <= uy);
}

int main(int argc, char* argv[])
{
	assert(float_le(-0, +0));
	assert(float_le(+0, -0));
	assert(float_le(0, 3));
	assert(float_le(-4, -0));
	assert(float_le(-4, 4));
	return 0;
}
