#ifndef _THEPACMANGAME_H
#define _THEPACMANGAME_H

#include "io_utils.h"
#include "Board.h"
#include <queue>

class ThePacmanGame {
  
    Pacman player;
    int numOfBoards;
    vector<int> pacmanMoves;
    vector<int> ghostsMoves;
    vector<int> fruitMoves;
    vector<int> gameMoves;
    int mode = 1;
    int boardNum = 1;
    int sleepTime = 200;
    int ifPause = 0;
    int score = 0;
    int numOfGhosts;
    Ghost ghost[4];
    Board board;
    Fruit fruit;
public:
    void init();
    void run();
    void chooseLevel();
    int checkCollisionPacman(int dir);
    int checkCollisionGhost(int dir, int ghostNum);
    void mainMenu();
    void instructions();
    void pause(int& dir, int& life, int& lastDir, int& flag);
    int endGameConditions(const int life,int &flag);
    void setNumOfBoards(int num) { numOfBoards = num; };
    void winGame();
    void lostGame();
    void yummy(int life); /* check if the pacman ate a bread crumb */
    void checkValidKey(int key, int& dir, int& lastDir, int& life, int& flag); /* checks if the player input is valid */
    void printCreatures();
    void movingThroughTunnel();
    void ghostMovementNovice(int* ghostDir, int& countMovment);
    void ghostMovementGood(int* ghostDir, int& countMovment);
    void GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir);
    void avoidTunnels(int ghostDir[]); /* to not let the ghosts enter the tunnels */
        void ghostMovementBest();
    vector<int> shortestPath(char mat[][80], int rRow, int rCol, Point src, Point dest);
    struct Node {
        Point pt;
        int dist;
        Node(Point _pt, int _dist) { pt = _pt; dist = _dist; }
    };
    void selectedMovmentDiff(int* ghostDir, int& countSteps);
    void settings();
    void selectGameSpeed();
    void initFruit();
    void fruitMovment();
    void avoidTunnelsFruit();
    int getGameMode() { return mode; }
    int checkCollisionFruit();
    void setmode(int k) { mode = k;}
    void pacmanEatFruit();
    void ghostEatFruit();
    void saveMode();
};
#endif