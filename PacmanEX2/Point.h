#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"


using namespace std;

class Point {
	int x = 3, y = 1;
public:
	void setXandY(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch); /*to draw the figure*/
	void movePacman(int direction);
	void moveGhost(int direction);
	int getX() { return x; };
	int getY() { return y; };
};

#endif