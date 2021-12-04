#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"


using namespace std;

class Point {
	int x = 25, y = 1;
	int firstx = 0, firsty = 0;
public:
	void setXandY(int _x, int _y) {
		x = firstx = _x;
		y = firsty = _y;
	}
	void draw(char ch); /*to draw the figure*/
	void movePacman(int direction);
	void moveGhost(int direction);
	int getX() { return x; };
	int getY() { return y; };
	int getfirstX() { return firstx; };
	int getfirstY() { return firsty; };
};

#endif