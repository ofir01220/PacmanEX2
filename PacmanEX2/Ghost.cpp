#include "Ghost.h"


void Ghost::move()
{
	body.draw(' ');
	body.moveGhost(direction);
	body.draw(figure);
}

void Ghost::randDirection(int dir, int& count) {

	if (count == 20) {
		dir = rand() % 4;
		count = 0;
	}

	setDirection(dir);
}
