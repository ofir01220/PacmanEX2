#include "Point.h"

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch;
	gotoxy(0, 24);
}

void Point::move(int direction) {
	switch (direction) {
	case 0: // UP
		y = y - 1;
		break;
	case 1: // DOWN
		y = y + 1;
		break;
	case 2: // LEFT
		x = x - 1;
		break;
	case 3: // RIGHT
		x = x + 1;
		break;

	}

}