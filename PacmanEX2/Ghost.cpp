#include "Ghost.h"

void Ghost::randDirection(int dir, int& count) {

	if (count == 20) {
		dir = rand() % 4;
		count = 0;
	}

	setDirection(dir);
}
