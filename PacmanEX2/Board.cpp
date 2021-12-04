#include "Board.h"


void Board::PrintBoard() { //print the game screan.
	for (int i = 0; i < rowboard1; i++) {
		for (int k = 0; k < colboard1; k++) {
				cout << this->boardArr[i][k];
		}
		cout << endl;
	}
}

/*void Board::activateBoard()
{
	char board2[ROW][COLUMN] = {

		"+--------------------------------+     +--------------------------------------+",
		"|     .  .  .  .  .  .  .  .  .  .  .  |  .  .  .  .  .  .  .  .  .  .  .  .  |",
		"|  .  +--------------+  .  +-----+  .  |  .  +-----+  .  +--------------+  .  |",
		"|  .  ||||||||||||||||  .  |||||||  .  |  .  |||||||  .  ||||||||||||||||  .  |",
		"|  .  ||||||||||||||||  .  |||||||  .  |  .  |||||||  .  ||||||||||||||||  .  |",
		"|  .  +--------------+  .  +-----+  .  |  .  +-----+  .  +--------------+  .  |",
		"|  .  .  .  .  .  .  .  .  .  .  .  .  |  .  .  .  .  .  .  .  .  .  .  .  .  |",
		"|  .  +--------------+  .  +-----------+-----------+  .  +--------------+  .  |",
		"|  .  .  .  .  .  .  .  .  .  .  .  .     .  .  .  .  .  .  .  .  .  .  .  .  |",
		"+--------------------+  .  +--------+     +--------+  .  +--------------------+",
		"||||||||||||||||||||||  .  |                       |  .  ||||||||||||||||||||||",
		"+--------------------+  .  |     +--+_____+--+     |  .  +--------------------+",
		"                        .  |     |           |     |  .                        ",
		"+--------------------+  .  |     +-----------+     |  .  +--------------------+",
		"||||||||||||||||||||||  .  |                       |  .  ||||||||||||||||||||||",
		"+--------------------+  .  +-----------------------+  .  +--------------------+",
		"|  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  |",
		"|  .  +--------------+  .  +-----------------------+  .  +--------------+  .  |",
		"|  .  .  .  .  .  .  |  .  .  .  .  .  .  .  .  .  .  .  |  .  .  .  .  .  .  |",
		"+--------------+  .  +  .  +  .  +-----------+  .  +  .  +  .  +--------------+",
		"|  .  .  .  .  .  .  .  .  |  .  .  .  |  .  .  .  |  .  .  .  .  .  .  .  .  |",
		"|  .  +--------------------+-----+  .  +  .  +-----+  .  +---------------+ .  |",
		"|  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  |",
		"+--------------------------------+     +--------------------------------------+"
	};

	for (int i = 0; i < COLUMN; i++) {
		for (int k = 0; k < ROW; k++)
			this->boardArr[k][i] = board2[k][i];
	}
}*/

void Board::setBoardCol(int col) {
	this->colboard1 = col;

}
void Board::setBoardRow(int row) {
	this->rowboard1 = row;

}
void Board::activateBoard(Pacman &p, Ghost ghost[],int &numOfGhosts) {
	int i = 0, k = 0, countOfGhosts = 0;
	ifstream myReadFile;
	myReadFile.open("boardtest.txt");
	char niceChar;
	while (!myReadFile.eof()) {
		  niceChar = myReadFile.get();
		if (niceChar == '\n') {
			setBoardCol(k);
			k = -1;
			i++;
		}
		if (niceChar == '#')
			boardArr[i][k] = char(178);
		else if (niceChar == '%')
			boardArr[i][k] = ' ';
		else if (niceChar == ' ')
			boardArr[i][k] = '*';
		else if (niceChar == '@') {
			boardArr[i][k] = ' ';
			p.body.setXandY(k,i);
		}
		else if (niceChar == '$') {
			ghost[countOfGhosts].body.setXandY(k, i);
			countOfGhosts++;
			boardArr[i][k] = ' ';
		}
		
		k++;
	}
	setBoardRow(i + 1);
	numOfGhosts = countOfGhosts - 1;
}
void Board::initMat() {
	/*initilize hidden array of binnary numbers('1' - valid pos, '0' - not valid pos)*/
	for (int i = 0; i <  rowboard1; i++)
		for (int j = 0; j < colboard1; j++) {
			if (boardArr[i][j] == char(178))
				mat[i][j] = '0';
			else
				mat[i][j] = '1';
		}
}