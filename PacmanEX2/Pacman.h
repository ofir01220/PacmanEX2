#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Point.h"

class Pacman {
	int direction = 3, life = 3, crumbs = 0;
	char arrowKeys[10];
	char figure;
	Point body;
	friend class ThePacmanGame;
public:
	void setArrowKeys(const char* keys) { // "wsadWSAD"
		for (int i = 0; i < 10; i++)
			arrowKeys[i] = keys[i];
	}
	void setFigure(const char c) {
		figure = c;
	}
	void move();
	void setBody(int i, int k) { body.setXandY(i, k); };
	int getDirection(char key);
	void setDirection(int dir) {
		direction = dir;
	}
	void printBody(char ch)
	{
		body.draw(ch);
	}
};
#endif