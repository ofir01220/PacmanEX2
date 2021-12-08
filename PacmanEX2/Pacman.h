#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "GameObject.h"
#include <cstring>

class Pacman: public GameObject {
	int life = 3, crumbs = 0;
	char arrowKeys[10];

public:
	void setArrowKeys(const char* keys) { // "wsadWSAD"
		for (int i = 0; i < 10; i++)
			arrowKeys[i] = keys[i];
	}
	int getDirection(char key);
};
#endif