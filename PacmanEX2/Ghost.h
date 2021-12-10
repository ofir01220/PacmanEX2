#ifndef _GHOST_H_
#define _GHOST_H_
#include "Fruit.h"

class Ghost: public GameObject {
	int countmovment = 20;

public:
	void randDirection(int dir, int& count);
};
#endif

