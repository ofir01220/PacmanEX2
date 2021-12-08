#include "Pacman.h"

/*void Pacman::move()
{
	body.draw(' ');
	body.Point::move(direction);
	body.draw(figure);
}*/
int Pacman::getDirection(char key)
{
	for (int i = 0; i < 10; i++)
	{
		if (key == arrowKeys[i]) {
			if (i > 4)
				i = i - 5;
			return i;
		}

	}
	return -1;
}