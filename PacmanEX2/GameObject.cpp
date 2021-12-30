#include "GameObject.h"

void GameObject::move(bool t)
{
	body.draw(' ', t);
	body.Point::move(direction);
	body.draw(figure, t);
}

void GameObject::randDirection(int dir, int& count) {

	if (count == 20) {
		dir = rand() % 4;
		count = 0;
	}

	setDirection(dir);
}