#include "Point.h"

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch;
	gotoxy(0, 24);
}

void Point::movePacman(int dir) {
	switch (dir) {
	case 0: // UP
		y = y - 1;
		if (y < 1)
			y = 23;
		break;
	case 1: // DOWN
		y = y + 1;
		if (y > 23)
			y = 0;
		break;
	case 2: // LEFT
		x = x - 3;
		if (x < 1)
			x = 78;
		break;
	case 3: // RIGHT
		x = x + 3;
		if (x > 77)
			x = 0;
		break;
	case 4:
		break;
	}
}
void Point::moveGhost(int direction) {
	switch (direction) {
	case 0: // UP
		y = y - 1;
		break;
	case 1: // DOWN
		y = y + 1;
		break;
	case 2: // LEFT
		x = x - 3;
		break;
	case 3: // RIGHT
		x = x + 3;
		break;

	}

}