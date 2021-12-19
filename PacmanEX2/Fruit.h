#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "Pacman.h"

class Fruit : public GameObject {
	int lifeTime = 0;
	int holdTime = 40;
	int On = 0;
	int randNum;
public:
	void initRandNum() {
		randNum = (5 + rand() % 5);
	}
	int addScore() { return randNum; }
	void runningTime() {
		lifeTime--;
	}
	void holdingTime() {
		holdTime--;
	}
	const int LifeTime() const {
		return lifeTime;
	}
	const int HoldTime() const {
		return holdTime;
	}
	const int fruitOn() const { return On; }
	void setFruitOn(int i) { On = i; }
	void setLife(const int k) { lifeTime = k; }
	void setHold(const int k) { holdTime = k; }
	char drawchar() {return (char)randNum + '0';}
	};

#endif