#include "Board.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void Board::PrintBoard() { /*print the game screan.*/
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

void  Board::activateBoard(Pacman &p, Ghost ghost[], int &numOfGhosts, int boardNum) { /*Function to get the boards from the directory path or from the user.*/
	breadCrumbs = numOfGhosts = 0;
	clearBoard();
	initVec();
	int i = 0, k = 0, flag = 1, secFlag = 1;
	string trash;
	ifstream myReadFile;
	if (boardNum == -1) {
		if (boardname == "") {
			getBoardFromUser();
		}
		myReadFile.open(boardname);
		system("CLS");
	}
	else {
		if(numOfBoards != 0)
		myReadFile.open(fileNames[boardNum - 1]);
		else {
			cout << "There Are No '.screen' Files In The Directory Please Insert Screen Files" << endl;
			exit(0);
		}
	}
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
			if (i == 25) {
				i--;
				break;
			}
		}
		if (niceChar == '#') {
			boardArr[i][k] = char(178);
			botR.setXandY(k, i);
		}
		else if (niceChar == '%') {
			boardArr[i][k] = ' ';
			botR.setXandY(k, i);
		}
		else if (niceChar == ' ') {
			boardArr[i][k] = '*';
			breadCrumbs++;
			botR.setXandY(k, i);
		}
		else if (niceChar == '@') {
			boardArr[i][k] = ' ';
			p.body.setXandY(k, i);
			p.body.setStartPos(k, i);
			botR.setXandY(k, i);
		}
		else if (niceChar == '$') {
			ghost[numOfGhosts].body.setXandY(k, i);
			ghost[numOfGhosts].body.setStartPos(k, i);
			if(numOfGhosts < 4)
				numOfGhosts++;
			boardArr[i][k] = ' ';
			botR.setXandY(k, i);
		}
		else if (niceChar == '&') {
			setPrintXandY(k, i);
		}
		if (secFlag) {
			topL.setXandY(k, i);
			secFlag = 0;
		}
		if (k == 79) {
			getline(myReadFile, trash);
			k = -1;
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
			else {
				mat[i][j] = '1';
				if (boardArr[i][j] == '*') {
					posForFruit.push_back(Point(j, i));
				}
			}
		}
}

void Board::getBoardFromUser() {/*function to get the board by the user request.*/
	ifstream myReadFile;
	bool flag = FALSE;
	cout << "Please Enter A File's Name:";
	cin >> boardname;
	while (!flag) {
		if (boardname[boardname.size() - 1] != 'n' || boardname[boardname.size() - 2] != 'e' || boardname[boardname.size() - 3] != 'e'
			|| boardname[boardname.size() - 4] != 'r' || boardname[boardname.size() - 5] != 'c'
			|| boardname[boardname.size() - 6] != 's' || boardname[boardname.size() - 7] != '.') {
			system("CLS");
			cout << "Wrong input! please put a file's name with '.screen' in the end: ";
			cin >> boardname;
		}
		else
			flag = TRUE;
			
	}
	
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

Board::Board() { /*this constractur will get the file names from the directory path as we create a board object.*/
	std::string path = ".";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().filename().extension() == ".screen") {
			string s = entry.path().filename().string();
			fileNames.push_back(s);
			numOfBoards++;
		}
	}
}

