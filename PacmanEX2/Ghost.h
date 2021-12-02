#ifndef _GHOST_H_
#define _GHOST_H_
#include "Pacman.h"
class Ghost {
	int direction = 3;
	char figure;
	int countmovment = 20;
	Point body;
	friend class ThePacmanGame;
public:
	void setFigure(const char c) {
		figure = c;
	}

	void move();
	void randDirection(int dir, int& count);
	void setDirection(int dir) {
		direction = dir;
	}

	void printBody(char ch)
	{
		body.draw(ch);
	}
};
#endif

