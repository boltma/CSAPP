#include <assert.h>

/* Divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k)
{
	int w = sizeof(int) << 3;
	int mask = (1 << k) - 1;
	int bias = (x >> (w - 1)) & mask;
	return (x + bias) >> k;
}

int main(int argc, char const *argv[])
{
	int x = 0x80000007;
	assert(divide_power2(x, 0) == x);
	assert(divide_power2(x, 1) == x / 2);
	assert(divide_power2(x, 2) == x / 4);
	return 0;
}
