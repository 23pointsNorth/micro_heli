#include "Blob.h"

double operator-(const Blob &b1, const Blob &b2)
{
	 return abs(b1.pos.x - b2.pos.x) + abs(b1.pos.y - b2.pos.y) + abs(b1.area - b2.area);
}
