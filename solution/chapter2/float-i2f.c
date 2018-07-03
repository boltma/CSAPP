#include <assert.h>
#include <limits.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/* Compute (float) i */
float_bits float_i2f(int i)
{
	int sign = i & 0x80000000;
	int j = 0, k = 0;
	if (!i)
		return i;
	if (i < 0)
		i = -i;
	while (i >= 0)
	{
		i <<= 1;
		++j;
	}
	j = (158 - j) << 23;
	if ((i & 0xff) > 0x80 || (i & 0x1ff) == 0x180)
		k = 1;
	i = (i >> 8) & 0x007FFFFF;
	return sign + i + j + k;
}

int main(int argc, char const *argv[])
{
	int i = INT_MIN;
	float f;
	void* p = &f;
	do
	{
		f = i;
		assert(float_i2f(i) == *(unsigned *)p);
		if (i == INT_MAX)
			break;
		++i;
	}
	while (1);
	return 0;
}
