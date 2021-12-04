#ifndef _BOARD_H_
#define _BOARD_H_
#include "Ghost.h"
#include <fstream>
class Board {
	enum { ROW = 25, COLUMN = 80 };
	int rowboard1 = 0, colboard1 = 0, breadCrumbs = 0;
	char* boardname;
	char mat[25][80];
	char boardArr[25][80];
	Point topL, botR;
	friend class ThePacmanGame;

public:
  void activateBoard(Pacman& p, Ghost ghost[], int& numOfGhosts);
  void PrintBoard();
  void setBoardCol(int col);
  void setBoardRow(int row);
  void initMat();
  bool isValid(int row, int col) { return (row >= 0) && (col >= 0) && (row < rowboard1) && (col < colboard1); }
	
};
#endif

