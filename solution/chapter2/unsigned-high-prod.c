int signed_high_prod(int x, int y);

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int w = sizeof(unsigned) << 3;
	unsigned sgn_x = x >> (w - 1);
	unsigned sgn_y = y >> (w - 1);
	return signed_high_prod(x, y) + sgn_x * y + sgn_y * x;
};
