#ifndef _BOARD_H_
#define _BOARD_H_
#include "Ghost.h"
#include <fstream>
class Board {
	enum { ROW = 25, COLUMN = 80 };
	int rowboard1 = 0, colboard1 = 0;
	char* boardname;

public:
  char boardArr[25][80];
  void activateBoard(Pacman &p);
  void PrintBoard();
  void setBoardCol(int col);
  void setBoardRow(int row);
	
};
#endif

