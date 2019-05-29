#include "direction.h"

int sgn(int x)
{
	if (x > 0)
		return 1;
	if (x < 0)
		return -1;
	return 0;
}

Direction dir(int target, int floor)
{
	return Direction(sgn(target - floor));
}
