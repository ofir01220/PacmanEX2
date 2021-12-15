#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_
#include "Point.h"

class GameObject {
	int direction = UP;
	char figure;
	Point body;
	friend class ThePacmanGame;
	friend class Board;
public:
	void setFigure(const char c) 
	{
		figure = c;
	}
	void move();
	void randDirection(int dir, int& count);
	void setDirection(int dir) 
	{
		direction = dir;
	}
	void printBody(const char ch)
	{
		body.draw(ch);
	}
	virtual char drawchar() = 0;
};


#endif