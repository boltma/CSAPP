#include <stdio.h>

int int_shifts_are_arithmetic()
{
	int x = ~0;
	return !(x ^ (x >> 1));
}

int main(int argc, char const *argv[])
{
	if (int_shifts_are_arithmetic())
		printf("Int shifts are arithmetic on this machine.\n");
	else
		printf("Int shifts aren't arithmetic on this machine.\n");
	return 0;
}
