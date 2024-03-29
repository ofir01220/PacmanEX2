#ifndef _BOARD_H_
#define _BOARD_H_
#include "Ghost.h"
#include <fstream>
#include <vector>
class Board {
	const enum { ROW = 25, COLUMN = 80, BEGINNER = 0, INTERMIDATE = 1, EXPERT = 2 };
	int rowboard1 = 0, colboard1 = 0, breadCrumbs = 0;
	int difficult = BEGINNER;
	string boardname = "";
	vector<string> fileNames;
	char mat[25][80];
	char boardArr[25][80];
	int printx = 0, printy = 0, numOfBoards = 0;
	Point topL, botR;
	vector<Point> posForFruit;
	friend class ThePacmanGame;

public:
	void setPrintXandY(int x, int y) { printx = x; 
	printy = y; };
  void activateBoard(Pacman& p, Ghost ghost[], int& numOfGhosts, int boardNum);
  void PrintBoard();
  void clearBoard();
   Board();
  void setBoardCol(int col);
  void setBoardRow(int row);
  void initMat();
  bool isValid(int row, int col) { return (row >= 0) && (col >= 0) && (row < rowboard1) && (col < colboard1); }
  void setDiff(int diff) { difficult = diff; };
  void getBoardFromUser();
  void initVec();
};
#endif

