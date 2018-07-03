#include <assert.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	int len = sizeof(unsigned) / sizeof(char);
	int mask_1 = b;
	int mask_2 = 0xFF;
	i %= len;
	mask_1 <<= (i << 3);
	mask_2 <<= (i << 3);
	return (x & ~mask_2) | mask_1;
}

int main(int argc, char const *argv[])
{
	assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
	assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);
	return 0;
}
