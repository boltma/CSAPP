#include <assert.h>
#include <limits.h>

/* Determine whether arguments can be substracted without overflow */
int tsub_ok(int x, int y)
{
	int z = x - y;
	int mask = INT_MIN;
	int flag_x = x & mask;
	int flag = flag_x ^ (y & mask);
	return !(flag && ((z ^ x) & mask));
}

int main(int argc, char const *argv[])
{
	assert(!tsub_ok(0, INT_MIN));
	assert(!tsub_ok(INT_MAX, -1));
	assert(!tsub_ok(1, INT_MIN));
	assert(tsub_ok(1, -1));
	return 0;
}
