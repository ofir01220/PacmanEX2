#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "Pacman.h"

class Fruit : public GameObject {
	int lifeTime = 30;
	int holdTime = 20;
public:
	int addScore() {
		return (5 + rand() % 5);
	}
	void runningTime() {
		lifeTime--;
	}
	void holdingTime() {
		holdTime--;
	}
	int LifeTime() {
		return lifeTime;
	}
	int HoldTime() {
		return holdTime;
	}

};

#endif