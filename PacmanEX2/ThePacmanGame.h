#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_

#include "io_utils.h"
#include "Board.h"

class ThePacmanGame {
	enum { ESC = 27, UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3};
	Pacman player;
	int numOfBoards;
	int numOfGhosts;
	Ghost ghost[4];
	Board board[4];
public:
	void init();
	void run();
	int checkCollisionPacman(int dir);
	int checkCollisionGhost(int dir, int ghostNum);
	void mainMenu();
	void pause(int& score, int& dir, int& life, int& lastDir, int& flag);
	int endGameConditions(const int score, const int life);
	void setNumOfBoards(int num) { numOfBoards = num; };
	void winGame();
	void lostGame();
	void yummy(int& score, int life); /*check if the pacman ate a bread crumb*/
	void checkValidKey(int key, int& dir, int& lastDir, int& life, int& score, int& flag); /*checks if the player input is valid*/
	void printCreatures() {
		player.printBody((char)002);
		ghost[0].printBody((char)234);
		ghost[1].printBody((char)234);
	}
	void ghostMovementNovice(int* ghostDir, int& countMovment);
    void ghostMovementBest(int* ghostDir, int& countMovment);
	void GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir, const int score);
	void getOutOfBox(int ghostDir[2]); /*a function to make the ghosts exit the init position*/
	void avoidTunnels(int ghostDir[2]);/*to not let the ghosts enter the tunnels*/
	void findPath(int a, int b, int ghostNum, int mainDir, int secDir, int thirdDir, int lastDir);

};
#endif