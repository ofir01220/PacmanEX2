#ifndef _THEPACMANGAME_H
#define _THEPACMANGAME_H

#include "io_utils.h"
#include "Board.h"
#include <vector>
#include <queue>


class ThePacmanGame {
    enum { ESC = 27, UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
    Pacman player;
    int numOfBoards;
    int numOfGhosts;
    Ghost ghost[4];
    Board board;
public:
    void init();
    void run();
    int checkCollisionPacman(int dir);
    int checkCollisionGhost(int dir, int ghostNum);
    void mainMenu();
    void instructions();
    void chooseLevel();
    void pause(int& score, int& dir, int& life, int& lastDir, int& flag);
    int endGameConditions(const int score, const int life);
    void setNumOfBoards(int num) { numOfBoards = num; };
    void winGame();
    void lostGame();
    void yummy(int& score, int life); /* check if the pacman ate a bread crumb */
    void checkValidKey(int key, int& dir, int& lastDir, int& life, int& score, int& flag); /* checks if the player input is valid */
    void printCreatures();
    void movingThroughTunnel();
    void ghostMovementNovice(int* ghostDir, int& countMovment);
    void GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir, const int score);
    void avoidTunnels(int ghostDir[2]); /* to not let the ghosts enter the tunnels */
        void ghostMovementBest();
    vector<int> shortestPath(char mat[][80], int rRow, int rCol, Point src, Point dest);
    struct Node {
        Point pt;
        int dist;
        Node(Point _pt, int _dist) { pt = _pt; dist = _dist; }
    };

};
#endif