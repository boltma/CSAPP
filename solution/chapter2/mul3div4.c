#include <assert.h>

/* Compute 3*x/4 */
int mul3div4(int x)
{
	int mul3 = (x << 1) + x;
	int w = sizeof(int) << 3;
	int bias = (mul3 >> (w - 1)) & 3;
	return (mul3 + bias) >> 2;
}

int main(int argc, char* argv[])
{
	int x = 0x87654321;
	assert(mul3div4(x) == x * 3 / 4);
	return 0;
}
