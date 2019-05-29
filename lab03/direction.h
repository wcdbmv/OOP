#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
	down = -1,
	stay = 0,
	up = 1
};

Direction dir(int target, int floor);

#endif // DIRECTION_H
