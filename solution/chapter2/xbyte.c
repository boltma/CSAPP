#include <assert.h>

/* Declaration of data type where 4 bytes are packed into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum)
{
	return (int) word << ((3 - bytenum) << 3) >> 24;
}

int main(int argc, char const *argv[])
{
	assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
	assert(xbyte(0x00112233, 2) == 0x11);
	return 0;
}
