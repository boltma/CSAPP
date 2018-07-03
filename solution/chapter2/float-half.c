#include <assert.h>
#include <limits.h>
#include <math.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f)
{
	if ((f & 0x7F800000) == 0 || (f & 0x7F800000) == 0x800000)
	{
		if ((f & 3) == 3)
			f += 1;
		f = ((f >> 1) & 0xFFFFFF) | (f & 0x80000000);
	}
	else if ((f & 0x7F800000) != 0x7F800000)
		f -= 0x800000;
	return f;
}

int main(int argc, char const *argv[])
{
	int i = INT_MIN;
	float f, k;
	void *p = &i, *q = &k;
	do
	{
		f = *(float *)p;
		k = isfinite(f) ? f / 2 : f;
		assert(float_half(i) == *(unsigned *)q);
		if (i == INT_MAX)
			break;
		++i;
	}
	while (1);
	return 0;
}
