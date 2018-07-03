#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian()
{
	int x = 0xFF;
	byte_pointer start = (byte_pointer)&x;
	if (start[0])
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	if (is_little_endian())
		printf("This is a little endian machine.\n");
	else
		printf("This is a big endian machine.\n");
	return 0;
}
