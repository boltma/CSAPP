#include <assert.h>
#include <limits.h>
#include <math.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f)
{
	if ((f & 0x7F800000) != 0x7F800000 || (f & 0x7FFFFF) == 0)
		f &= 0x7FFFFFFF;
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
		k = isnan(f) ? *(float *)p : fabs(f);
		assert(float_absval(i) == *(unsigned *)q);
		if (i == INT_MAX)
			break;
		++i;
	}
	while (1);
	return 0;
}
