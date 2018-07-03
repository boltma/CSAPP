#include <assert.h>
#include <limits.h>
#include <math.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f)
{
	if ((f & 0x7FFFFFFF) > 0x7F800000)
		return f;
	return f ^ 0x80000000;
}

int main(int argc, char const *argv[])
{
	int i = INT_MIN;
	float f, k;
	void *p = &i, *q = &k;
	do
	{
		f = *(float *)p;
		k = isnan(f) ? f : -f;
		assert(float_negate(i) == *(unsigned *)q);
		if (i == INT_MAX)
			break;
		++i;
	}
	while (1);
	return 0;
}
