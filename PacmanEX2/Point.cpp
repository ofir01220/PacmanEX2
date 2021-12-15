#include "Point.h"

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch;
	gotoxy(0, 24);
}

void Point::move(int direction) {
	switch (direction) {
	case UP: 
		y = y - 1;
		break;
	case DOWN: 
		y = y + 1;
		break;
	case LEFT: 
		x = x - 1;
		break;
	case RIGHT: 
		x = x + 1;
		break;

	}

}