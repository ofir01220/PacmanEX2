#include "GameObject.h"

void GameObject::move()
{
	body.draw(' ');
	body.Point::move(direction);
	body.draw(figure);
}

void GameObject::randDirection(int dir, int& count) {

	if (count == 20) {
		dir = rand() % 4;
		count = 0;
	}

	setDirection(dir);
}