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
	initVec();
	int i = 0, k = 0, flag = 1, secFlag = 1;
	ifstream myReadFile;
	if (boardNum == 5) {
		if (boardname == "") {
			getBoardFromUser();
		}
		myReadFile.open(boardname);
		system("CLS");
	}
    else if (boardNum == 1)
		myReadFile.open("pacman_1.screen.txt");
	else if (boardNum == 2)
		myReadFile.open("pacman_2.screen.txt");
	else if(boardNum == 3){}

	char niceChar = ' ', lastChar = ' ';
	while (!myReadFile.eof()) {
		if(lastChar != '&' || niceChar != '\n')
			lastChar = niceChar;
		  niceChar = myReadFile.get();
		if (niceChar == '\n') {
			if (flag) {
				setBoardCol(k + 1);
				flag = 0;
			}
			k = -1;
			i++;
		}
		if (niceChar == '#') {
			boardArr[i][k] = char(178);
			botR.setXandY(k, i);
		}
		else if (niceChar == '%') {
			boardArr[i][k] = ' ';
			posForFruit.push_back(Point(k, i));
		}
		else if (niceChar == ' ') {
			boardArr[i][k] = '*';
			breadCrumbs++;
			posForFruit.push_back(Point(k, i));
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
		else if (niceChar == '&') {
			setPrintXandY(k, i);
		}
		if (secFlag) {
			topL.setXandY(k, i);
			secFlag = 0;
		}
		k++;
	}
	setBoardRow(i + 1);
	for (int n = printy; n < printy + 3; n++) {
		for (int m = printx; m < printx + 20; m++) {
			if (boardArr[n][m] == '*')
				breadCrumbs--;
			boardArr[n][m] = ' ';
		}
		if (n > i)
			botR.setXandY(botR.getX(), n);
	}
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

void Board::getBoardFromUser() {
	ifstream myReadFile;
	cout << "Please Enter A File's Name:";
	cin >> boardname;
	boardname += ".txt";
	myReadFile.open(boardname);
	while (!myReadFile.is_open()) {
		system("CLS");
		cout << "No File By The Name:" << boardname << " Was Found, Please Try Again." << endl;

			cout << "Please Enter A File's Name:";
			cin >> boardname;
			myReadFile.open(boardname);
		
    }
	myReadFile.close();
}

void Board::initVec() {
	while (posForFruit.size() != 0)
		posForFruit.pop_back();
}


