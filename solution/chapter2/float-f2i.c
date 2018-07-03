#include <assert.h>
#include <limits.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

/*
 * Compute (int) f.
 * If conversion causes overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	int i;
	if (exp != 0)
		frac |= 0x800000;
	if (exp >= 158)
		i = 0x80000000;
	else if (exp >= 150)
		i = frac << (exp - 150);
	else if (exp >= 127)
		i = frac >> (150 - exp);
	else
		i = 0;
	return sign ? -i : i;
}

int main(int argc, char const *argv[])
{
	int i = INT_MIN;
	float f;
	void* p = &i;
	do
	{
		f = *(float *)p;
		assert(float_f2i(i) == (int)f);
		if (i == INT_MAX)
			break;
		++i;
	}
	while (1);
	return 0;
}
