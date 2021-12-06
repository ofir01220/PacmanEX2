#include "Board.h"


void Board::PrintBoard() { //print the game screan.
	for (int i = 0; i < rowboard1; i++) {
		for (int k = 0; k < colboard1; k++) {
				cout << this->boardArr[i][k];
		}
		cout << endl;
	}
}

void Board::clearBoard() {
	for (int i = 0; i < ROW; i++) 
		for (int k = 0; k < COLUMN; k++) {
			boardArr[i][k] = '\0';
			mat[i][k] = '\0';
		}
}

void Board::setBoardCol(int col) {
	this->colboard1 = col;
}

void Board::setBoardRow(int row) {
	this->rowboard1 = row;
}

void Board::activateBoard(Pacman &p, Ghost ghost[], int &numOfGhosts, int boardNum) {
	breadCrumbs = numOfGhosts = 0;
	clearBoard();
	int i = 0, k = 0, flag = 1, secFlag = 1;
	string userFile = "";
	ifstream myReadFile;
	if (boardNum == 1)
		myReadFile.open("board_01.txt");
	else if (boardNum == 2)
		myReadFile.open("board_02.txt");
	else if(boardNum == 3){}
	else if (boardNum == 5 ) {
		if (boardname == "") {
			cout << "Enter a file's name (then press ENTER): ";
			cin >> boardname;
		}
		myReadFile.open(boardname);
		system("CLS");
	}

	char niceChar = ' ', lastChar = ' ';
	while (!myReadFile.eof()) {
		if(lastChar != '&' || niceChar != '\n')
			lastChar = niceChar;
		  niceChar = myReadFile.get();
		if (niceChar == '\n') {
			if (flag) {
				if (lastChar != '&') {
					setBoardCol(k + 1);
					flag = 0;
				}
				else if (lastChar == '&' && (k == 1) || (k == 0)){}
				else {
					setBoardCol(k + 21);
					flag = 0;
				}
			}
			k = -1;
			i++;
		}
		if (niceChar == '#') {
			boardArr[i][k] = char(178);
			if (secFlag) {
				topL.setXandY(k, i);
				secFlag = 0;
			}
			botR.setXandY(k, i);
		}
		else if (niceChar == '%')
			boardArr[i][k] = ' ';
		else if (niceChar == ' ') {
			boardArr[i][k] = '*';
			breadCrumbs++;
		}
		else if (niceChar == '@') {
			boardArr[i][k] = ' ';
			p.body.setXandY(k, i);
			p.body.setStartPos(k, i);
		}
		else if (niceChar == '$') {
			ghost[numOfGhosts].body.setXandY(k, i);
			ghost[numOfGhosts].body.setStartPos(k, i);
			numOfGhosts++;
			boardArr[i][k] = ' ';
		}
		else if (niceChar == '&') 
			setPrintXandY(k, i);

		k++;
	}
	setBoardRow(i + 1);
	myReadFile.close();
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





