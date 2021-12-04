#include "ThePacmanGame.h"

void ThePacmanGame::init()
{
	player.setArrowKeys("wxadsWXADS");
	player.setFigure((char)002);
	ghost[0].setFigure((char)234);
	ghost[1].setFigure((char)234);
	board.activateBoard(player);
	board.PrintBoard();
	//player.body.setXandY(3, 1);
	ghost[0].body.setXandY(36, 12);
	ghost[1].body.setXandY(48, 12);
}
void ThePacmanGame::run()
{
	char key = 0;
	int dir = UP, start = FALSE, score = 0, life = 3, lastDir, ghostDelay = FALSE, ghostDir[2] = { 0,0 }, flag = 0, countMovment = 0;
	printCreatures();
	gotoxy(0, 24);
	cout << "score: " << score << ' ' << "life: " << life;
	do {
		lastDir = dir; /*if the player selects a direction that will hit a wall, we avoid that direction and continue on the last direction (see lines 29-31)*/
		if (_kbhit())
		{
			key = _getch();
			checkValidKey(key, dir, lastDir, life, score, flag); /*check if the pressed key is a valid key(move or pause)*/
		}
		start = checkCollisionPacman(dir);
		if (!start) {
			dir = lastDir;
			start = checkCollisionPacman(dir);
		}
		player.setDirection(dir);
		if (start) {
			player.move();
			yummy(score, life); /*checks if the pacman ate a crumb.*/
			flag = 1;
		}
		if (flag == 1) /*starts the sleep function only if the game starts*/
			Sleep(225);

		GhostEatPacman(life, flag, start, dir, ghostDir, score);
		if ((ghostDelay == TRUE) && (flag)) { /*to make the ghost go 2X slower than the pacman*/
			ghostMovementNovice(ghostDir, countMovment);
			ghostDelay = FALSE;
		}
		else
			ghostDelay = TRUE;
		GhostEatPacman(life, flag, start, dir, ghostDir, score);
	} while (endGameConditions(score, life));

	system("CLS");
}



int ThePacmanGame::checkCollisionPacman(int dir) /*check if the next move is valid.*/
{
	switch (dir) {
	case 0: // UP
		if (board.boardArr[player.body.getY() - 1][player.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 1: // DOWN
		if (board.boardArr[player.body.getY() + 1][player.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 2: // LEFT
		if  (board.boardArr[player.body.getY()][player.body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case 3: // (3)- RIGHT
		if (board.boardArr[player.body.getY()][player.body.getX() + 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case 4: // (4)- STAY
		return 1;
		break;
	default:
		return 0;
		break;
	}

}

void ThePacmanGame::mainMenu() {
	char choice = '0';

	while (choice == '0') {
		cout << "*******************" << endl;
		cout << "******PACMAN*******" << endl;
		cout << "*******************" << endl << endl;
		cout << "To Start The Game Please Press 1" << endl;
		cout << "For Instructions Please press 8" << endl;
		cout << "If You Wish To Exit Please Press 9" << endl;
		choice = _getch();
		if (choice != '1' && choice != '8' && choice != '9')
			choice = '0';

		if (choice == '8') { /*INSTRUCTIONS*/
			system("CLS");
			cout << "********************" << endl;
			cout << "****INSTRUCTIONS****" << endl;
			cout << "********************" << endl << endl;
			cout << "1. To move the Pacman, please press the 'w'(UP),'a'(LEFT),'x'(DOWN),'d'(RIGHT) keys." << endl;
			cout << "2. If you wish Pacman to stay in his current position please press 's'." << endl;
			cout << "3. The Pacman starts with 3 life points." << endl;
			cout << "4. When the ghost touches Pacman, he loses a life point and starts from the starting point." << endl;
			cout << "5. To win the game, Pacman has to eat all of the dots (each dot gives one point)." << endl;
			cout << "6. The Pacman can move through the tunnels to move to the other side of the map." << endl;
			cout << "7. Have FUN don't DIE!." << endl << endl;
			cout << "If you wish to return to the main menu please press any key." << endl;
			while (!_kbhit())
				choice = '0';
			char trash = _getch(); /*To avoid the char we recive on the _kbhit()*/
		}
		if (choice == '9') {
			system("CLS"); 
			cout << "***GOOD BYE***" << endl;
			exit(0);
		}
		system("CLS");
	}
}


void ThePacmanGame::pause(int& score, int& dir, int& life, int& lastDir, int& flag) {
	system("CLS");
	cout << "******************" << endl;
	cout << "******PAUSE*******" << endl;
	cout << "******************" << endl << endl;
	cout << "If you wish to restart the game please press 'R'." << endl;
	cout << "If you wish to return to the main menu please press 'M'." << endl;
	cout << "If you wish to return to the game please press any other key." << endl;
	while (!_kbhit()) {

	}
	char trash = _getch();
	if (trash == 'M' || trash == 'm') { /*if the player choose m for menu that the game or will restart or will exit so we init the game*/
		score = 0;
		life = 3;
		dir = lastDir = 0;
		flag = 0;
		board.activateBoard(player);
		//player.body.setXandY(3, 1);
		ghost[0].body.setXandY(36, 12);
		ghost[1].body.setXandY(48, 12);
		system("CLS");
		mainMenu();
	}
	if (trash == 'r' || trash == 'R') {/*RESTART*/
		score = 0;
		life = 3;
		dir = lastDir = 0;
		flag = 0;
		init(); /*to init the game from the begining */
	}
	system("CLS");
	board.PrintBoard();
	printCreatures();
	gotoxy(0, 24);
	cout << "score: " << score << ' ' << "life: " << life;
}
int ThePacmanGame::endGameConditions(const int score, const int life) {
	if (score == 223) { /*max point.*/
		winGame();
		return 0;
	}
	else if (life == 0) {
		lostGame();
		return 0;
	}
	return 1; /*continue the game.*/
}

void ThePacmanGame::winGame() {
	system("CLS");
	cout << "******************" << endl;
	cout << "*****YOU WON!*****" << endl;
	cout << "******************" << endl << endl;
	cout << "If you wish to return to the main menu please press any key." << endl;
	while (!_kbhit()) {

	}
	char trash = _getch();
	system("CLS");
}

void ThePacmanGame::lostGame() {
	system("CLS");
	cout << "*******************" << endl;
	cout << "*****GAME OVER*****" << endl;
	cout << "*******************" << endl << endl;
	cout << "If you wish to return to the main menu please press any key." << endl;
	while (!_kbhit()) {

	}
	char trash = _getch();
	system("CLS");
}

void ThePacmanGame::yummy(int& score, int life) {
	if (board.boardArr[player.body.getY()][player.body.getX()] == '*') { /*if the user ate crumb.*/
		board.boardArr[player.body.getY()][player.body.getX()] = ' '; /*we delete the crumb from the board*/
		score++;
		gotoxy(0, 24);
		cout << "score: " << score << ' ' << "life: " << life;

	}
}

void ThePacmanGame::checkValidKey(int key, int& dir, int& lastDir, int& life, int& score, int& flag) {
	if (key == ESC)
		pause(score, dir, life, lastDir, flag);


	if ((player.getDirection(key)) != -1)
		dir = player.getDirection(key);
}

void ThePacmanGame::ghostMovementNovice(int* ghostDir, int& countMovment) {
	int ghost0X = ghost[0].body.getX(), ghost1X = ghost[1].body.getX(), ghost0Y = ghost[0].body.getY(), ghost1Y = ghost[1].body.getY();

	getOutOfBox(ghostDir); /*Get out from the starting boxand made an option to go to the bottom of the map.*/

	if (countMovment == 20) {
		ghostDir[0] = rand() % 4;
		ghostDir[1] = rand() % 4;
		countMovment = 0;
	}

	avoidTunnels(ghostDir);

	while (!checkCollisionGhost(ghostDir[0], 0))  /*Checks if the next move is not valid.*/
		ghostDir[0] = rand() % 4;

	ghost[0].setDirection(ghostDir[0]);
	ghost[0].move();

	if (board.boardArr[ghost0Y][ghost0X] == '*') {
		gotoxy(ghost0X, ghost0Y);
		cout << '*';
	}
	while (!checkCollisionGhost(ghostDir[1], 1)) /*Checks if the next move is not valid.*/
		ghostDir[1] = rand() % 4;

	ghost[1].setDirection(ghostDir[1]);
	ghost[1].move();
	if (board.boardArr[ghost1Y][ghost1X] == '*') {
		gotoxy(ghost1X, ghost1Y);
		cout << '*';
	}
	countMovment++;
}


int ThePacmanGame::checkCollisionGhost(int dir, int ghostNum) {
	switch (dir) {
	case 0: // UP
		if (board.boardArr[ghost[ghostNum].body.getY() - 1][ghost[ghostNum].body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 1: // DOWN
		if (board.boardArr[ghost[ghostNum].body.getY() + 1][ghost[ghostNum].body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 2: // LEFT
		if (board.boardArr[ghost[ghostNum].body.getY()][ghost[ghostNum].body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case 3: // (3)- RIGHT
		if (board.boardArr[ghost[ghostNum].body.getY()][ghost[ghostNum].body.getX() + 1] == char(178))
			return 0;
		else
			return 1;

		break;
	default:
		return 0;
		break;
	}

}

void ThePacmanGame::GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir, const int score) {
	int x[2], y[2], xPlayer = player.body.getX(), yPlayer = player.body.getY();
	x[0] = ghost[0].body.getX();
	y[0] = ghost[0].body.getY();
	x[1] = ghost[1].body.getX();
	y[1] = ghost[1].body.getY();
	for (int i = 0; i < 2; i++) {
		if ((xPlayer == x[i]) && (yPlayer == y[i])) { /*If one of the ghosts eat pacman.*/
			--life;
			flag = 0;
			start = 0;
			ghost[0].body.setXandY(36, 12);
			ghost[1].body.setXandY(42, 12);
			player.body.setXandY(3, 1);
			printCreatures();
			ghost[0].setDirection(0);
			ghost[1].setDirection(0);
			player.setDirection(0);
			gotoxy(x[0], y[0]);
			cout << board.boardArr[y[0]][x[0]];
			gotoxy(x[1], y[1]);
			cout << board.boardArr[y[1]][x[1]];
			dir = ghostDir[0] = ghostDir[1] = 0;
			break; /*avoid from being eaten twice (if the ghosts are on the same spot)*/
		}
	}
	gotoxy(0, 24);
	cout << "score: " << score << ' ' << "life: " << life;
}

void ThePacmanGame::getOutOfBox(int ghostDir[2]) {
	int ghost0X = ghost[0].body.getX(), ghost1X = ghost[1].body.getX(), ghost0Y = ghost[0].body.getY(), ghost1Y = ghost[1].body.getY();

	if (((ghost1X == 39) && (ghost1Y == 12)) || ((ghost1X == 39) && (ghost1Y == 10))) /*To get the ghosts out of the starting pos */
		ghostDir[1] = UP;
	if (((ghost0X == 39) && (ghost0Y == 12)) || ((ghost0X == 39) && (ghost0Y == 10))) /*To get the ghosts out of the starting pos */
		ghostDir[0] = UP;
	if (((ghost1X == 24) && (ghost1Y == 8)) || ((ghost1X == 54) && (ghost1Y == 8))) /*To make the ghost an option go to the bottom of the map*/
		ghostDir[1] = rand() % 4;
	if (((ghost0X == 24) && (ghost0Y == 8)) || ((ghost0X == 54) && (ghost0Y == 8))) /*To make the ghost an option go to the bottom of the map*/
		ghostDir[0] = rand() % 4;
}

void ThePacmanGame::avoidTunnels(int ghostDir[2]) {
	int ghost0X = ghost[0].body.getX(), ghost1X = ghost[1].body.getX(), ghost0Y = ghost[0].body.getY(), ghost1Y = ghost[1].body.getY();

	if (ghost0Y == 0)
		ghostDir[0] = DOWN;
	if (ghost0Y == 23)
		ghostDir[0] = UP;
	if (ghost1Y == 0)
		ghostDir[1] = DOWN;
	if (ghost1Y == 23)
		ghostDir[1] = UP;
	if (ghost0X == 0)
		ghostDir[0] = RIGHT;
	if (ghost0X == 78)
		ghostDir[0] = LEFT;
	if (ghost1X == 0)
		ghostDir[0] = RIGHT;
	if (ghost1X == 78)
		ghostDir[0] = LEFT;
}

void ThePacmanGame::findPath(int a, int b, int ghostNum, int mainDir, int secDir, int thirdDir, int lastDir) {
	if (!checkCollisionGhost(mainDir, ghostNum)) {
		if (a < b && ghost[ghostNum].direction != lastDir) {
			if (!checkCollisionGhost(secDir, ghostNum)) {
				if (!checkCollisionGhost(thirdDir, ghostNum)) {
					ghost[ghostNum].setDirection(lastDir);
				}
				else ghost[ghostNum].setDirection(thirdDir);
			}
			else ghost[ghostNum].setDirection(secDir);
		}
		else {
			if (!checkCollisionGhost(thirdDir, ghostNum)) {
				if (!checkCollisionGhost(lastDir, ghostNum)) {
					ghost[ghostNum].setDirection(secDir);
				}
				else ghost[ghostNum].setDirection(lastDir);
			}
			else ghost[ghostNum].setDirection(thirdDir);
		}
	}
	else ghost[ghostNum].setDirection(mainDir);
}




