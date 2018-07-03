#include <assert.h>
#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
	int sum = x + y;
	int mask = INT_MIN;
	int flag_x = x & mask;
	int m = flag_x ^ (y & mask);
	int flag = !m && ((x ^ sum) & mask);
	flag && ((!flag_x || (sum = INT_MIN)) && (flag_x || (sum =  INT_MAX)));
	return sum;
}

int main(int argc, char const *argv[])
{
	assert(saturating_add(0x11, 0x22) == 0x33);
	assert(saturating_add(INT_MAX, 0x1234) == INT_MAX);
	assert(saturating_add(INT_MIN, -0x1234) == INT_MIN);
	assert(saturating_add(0x1234, INT_MAX) == INT_MAX);
	assert(saturating_add(-0x1234, INT_MIN) == INT_MIN);
	return 0;
}
