#include "ThePacmanGame.h"

void ThePacmanGame::init()
{
	setSpeedInLoad();
	player.setArrowKeys("wxadsWXADS");
	player.setFigure(player.drawchar());
	board.activateBoard(player, ghost, this->numOfGhosts, boardNum);
	for (int i = 0; i < numOfGhosts; i++)
		ghost[i].setFigure(ghost[i].drawchar());
	player.initilizeCrumbs(board.breadCrumbs);
	if (mode != 3) {
		board.PrintBoard();
		printCreatures();
	}
	board.initMat();
}
void ThePacmanGame::run()
{
	srand((int)time(NULL));
	char key = 0;
	int dir = UP, start = FALSE, life = 3, lastDir, ghostDelay = FALSE, ghostDir[4] = { 0,0 }, flag = 0, countMovment = 0, stop = 0;
	bool dontPrint = TRUE;
	if (mode == 3)
		dontPrint = FALSE;
	if (mode != 3) {
		printCreatures();
		gotoxy(board.printx, board.printy);
		cout << "score: " << score << ' ' << "life: " << life;
		gotoxy(board.printx, board.printy + 1);
		cout << "Difficult Level: " << board.difficult + 1;
	}
	if (mode == 2 || mode == 3)
		ghostDelay = TRUE;
	do {
		lastDir = dir; /*if the player selects a direction that will hit a wall, we avoid that direction and continue on the last direction (see lines 29-31)*/
		if (_kbhit() && mode != 2 && mode != 3) {
			key = _getch();
			if ((player.getDirection(key)) != -1)
				ifPause = 1;
			checkValidKey(key, dir, lastDir, life, flag, stop); /*check if the pressed key is a valid key(move or pause)*/
		}

		if ((mode == 2  || mode == 3) && stop == 0) {
			getInputs();
			ifPause = 1;
			stop = 1;
			reverse(pacmanMoves.begin(), pacmanMoves.end());
			reverse(ghostsMoves.begin(), ghostsMoves.end());
			reverse(fruitMoves.begin(), fruitMoves.end());
			reverse(gameMoves.begin(), gameMoves.end());
		}
		if ((mode == 2 || mode == 3) && ifPause) {
				dir = pacmanMoves[pacmanMoves.size() - 1];
				pacmanMoves.pop_back();
		}
		start = checkCollisionPacman(dir);
		if (!start && (mode != 2 && mode != 3)) {
			dir = lastDir;
			start = checkCollisionPacman(dir);
		}
		player.setDirection(dir);
		if (start && ifPause) {
			player.move(dontPrint);
			if (mode == 1)
				pacmanMoves.push_back(dir);
			numOfMoves++;
			movingThroughTunnel(); /*let pacman an option to move through tunnels*/
			yummy(life); /*checks if the pacman ate a crumb.*/
			flag = 1;
		}
		else if (!start && ifPause && mode == 1) {
			pacmanMoves.push_back(dir);
			numOfMoves++;
		}
		else if (!start && ifPause && (mode == 2 || mode == 3)) {
			numOfMoves++;
		}

		Sleep(sleepTime);
		GhostEatPacman(life, flag, start, dir, ghostDir);
		pacmanEatFruit();
		
		if ((ghostDelay == TRUE) && (flag)) { /*to make the ghost go 2X slower than the pacman*/
			selectedMovmentDiff(ghostDir, countMovment, dontPrint);
			countMovment++;
			ghostDelay = FALSE;
			GhostEatPacman(life, flag, start, dir, ghostDir);
			pacmanEatFruit();
		}
		else {
			ghostDelay = TRUE;
		}
		if (mode == 3) 
			printWaitingTime();
		
	} while (endGameConditions(life, flag, stop));

	system("CLS");
}



int ThePacmanGame::checkCollisionPacman(const int dir) /*check if the next move is valid.*/
{
	switch (dir) {
	case UP:
		if (board.boardArr[player.body.getY() - 1][player.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case DOWN:
		if (board.boardArr[player.body.getY() + 1][player.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case LEFT:
		if (board.boardArr[player.body.getY()][player.body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case RIGHT:
		if (board.boardArr[player.body.getY()][player.body.getX() + 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case 4: // (4)- STAY
		return 0;
		break;
	default:
		return 0;
		break;
	}

}

void ThePacmanGame::mainMenu() {
	char choice = '0';
	boardNum = 1;
	board.boardname = "";
	while (choice == '0') {
		cout << "****************" << endl;
		cout << "*****PACMAN*****" << endl;
		cout << "****************" << endl << endl;
		cout << "To Start The Game Please Press 1" << endl;
		cout << "To Enter To The Settings Please Press 3" << endl;
		cout << "For Instructions Please press 8" << endl;
		cout << "If You Wish To Exit Please Press 9" << endl;
		choice = _getch();
		if (choice != '1' && choice != '8' && choice != '9' && choice != '3')
			choice = '0';
		if (choice == '3')
			settings();

		if (choice == '8') { /*INSTRUCTIONS*/
			instructions();
			while (!_kbhit())
				choice = '0';
			char trash = _getch(); /* To avoid the char we recive on the _kbhit() */
		}
		if (choice == '9') {
			system("CLS");
			cout << "***GOOD BYE***" << endl;
			exit(0);
		}
		system("CLS");
	}
}

void ThePacmanGame::instructions() {
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
	cout << "7. There are 3 boards to the game, if you wish to select your own board please go back and select settings." << endl;
	cout << "8. All 3 boards have diffrent difficulty of the ghosts, to change the difficult please go back and select settings." << endl;
	cout << "9. Have FUN don't DIE!." << endl << endl;
	cout << "If you wish to return to the main menu please press any key." << endl;
}

void ThePacmanGame::chooseLevel() {/*Choose the difficult of the game*/
	char choice = '0';
	while (choice == '0') {
		system("CLS");
		cout << "********************" << endl;
		cout << "****CHOOSE LEVEL****" << endl;
		cout << "********************" << endl << endl;
		cout << "To play BEGINNER mode, press 1." << endl;
		cout << "To play INTERMEDIANTE mode, press 2." << endl;
		cout << "To play EXPERT mode, press 3." << endl;
		cout << "To Go Back To Settings Press ESC" << endl;
		choice = _getch();
		if (choice != '1' && choice != '2' && choice != '3' && choice != '\x1b')
			choice = '0';
		else if (choice == '1') {
			board.difficult = 0;
			cout << "Difficult Set To BEGINNER";
		}
		else if (choice == '2') {
			board.difficult = 1;
			cout << "Difficult Set To INTERMEDIATE";
		}
		else if (choice == '3') {
			board.difficult = 2;
			cout << "Difficult Set To EXPERT";
		}
		else if (choice == '\x1b') {
			break;
		}

	}
}

void ThePacmanGame::pause(int& dir, int& life, int& lastDir, int& flag, int& stop) {
	system("CLS");
	cout << "******************" << endl;
	cout << "******PAUSE*******" << endl;
	cout << "******************" << endl << endl;
	cout << "If you wish to restart the game please press 'R'." << endl;
	cout << "If you wish to return to the main menu please press 'M'." << endl;
	cout << "To Enter To The Settings Please Press 'S'." << endl;
	cout << "If you wish to return to the game please press any other key." << endl;
	while (!_kbhit()) {

	}
	char trash = _getch();
	if (trash == 'M' || trash == 'm') { /*if the player choose m for menu that the game or will restart or will exit so we init the game*/
		ifPause = 0;
		score = 0;
		life = 3;
		dir = lastDir = 0;
		flag = 0;
		board.difficult = 0;
		stop = 0;
		makeEmptyVec();
		system("CLS");
		mainMenu();
		init();
	}
	if (trash == 'r' || trash == 'R') {/*RESTART*/
		ifPause = 0;
		score = 0;
		life = 3;
		dir = lastDir = 0;
		flag = 0;
		stop = 0;
		makeEmptyVec();
		system("CLS");
		init(); /*to init the game from the begining */
	}
	if (trash == 's' || trash == 'S') {
		settings();
		system("CLS");
		board.PrintBoard();
		printCreatures();
		ifPause = 0;
		flag = 0;
	}
	else {
		system("CLS");
		board.PrintBoard();
		printCreatures();
	}
	gotoxy(board.printx, board.printy);
	cout << "score: " << score << ' ' << "life: " << life;
	gotoxy(board.printx, board.printy + 1);
	cout << "Difficult Level: " << board.difficult + 1;
}

int ThePacmanGame::endGameConditions(const int life, int& flag, int& stop) {
	if (player.Crumbs() == 0 && (boardNum == board.numOfBoards || boardNum == -1)) { /*max point.*/
		check();
		EndGameMode3();
		if (mode != 3)
			winGame();
		score = 0;
		board.difficult = 0;
		flag = 0;
		boardNum = 1;
		ifPause = 0;
		if (mode == 1) {
			gameMoves.push_back(numOfMoves);
			saveMode();
		}
		makeEmptyVec();
		stop = 0;
		numOfMoves = 0;
		return 0;
	}
	else if (player.Crumbs() == 0) {
		check();
		if (mode == 1) {
			gameMoves.push_back(numOfMoves);
			saveMode();
		}
		makeEmptyVec();
		boardNum++;
		if (board.difficult != 2)
			board.difficult = board.difficult + 1;
		system("CLS");
		init();
		flag = 0;
		stop = 0;
		numOfMoves = 0;
	}
	else if (life == 0) {
		check();
		EndGameMode3();
		if (mode == 1) {
			gameMoves.push_back(numOfMoves);
			saveMode();
		}
		makeEmptyVec();
		if (mode != 3)
			lostGame();
		boardNum = 1;
		score = 0;
		stop = 0;
		numOfMoves = 0;
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

void ThePacmanGame::yummy(const int life) {
	if (board.boardArr[player.body.getY()][player.body.getX()] == '*') { /*if the user ate crumb.*/
		board.boardArr[player.body.getY()][player.body.getX()] = ' '; /*we delete the crumb from the board*/
		score++;
		player.eatCrumb();
		if (mode != 3) {
			gotoxy(board.printx, board.printy);
			cout << "score: " << score << ' ' << "life: " << life;
			gotoxy(board.printx, board.printy + 1);
			cout << "Difficult Level: " << board.difficult + 1;
		}
	}
}

void ThePacmanGame::checkValidKey(int key, int& dir, int& lastDir, int& life, int& flag, int& stop) {
	if (key == ESC)
		pause(dir, life, lastDir, flag, stop);


	if ((player.getDirection(key)) != -1)
		dir = player.getDirection(key);
}

void ThePacmanGame::ghostMovementNovice(int* ghostDir, int& countMovment, const bool dontPrint) {

	if (countMovment == 21) {
		ghostDir[0] = rand() % 4;
		ghostDir[1] = rand() % 4;
		ghostDir[2] = rand() % 4;
		ghostDir[3] = rand() % 4;
		countMovment = 0;
	}
	avoidTunnels(ghostDir);
	for (int i = 0; i < numOfGhosts; i++) {
		if (mode == 2 || mode == 3) {
			ghostDir[i] = ghostsMoves[ghostsMoves.size() - 1];
			ghostsMoves.pop_back();
		}
		while (!checkCollisionGhost(ghostDir[i], i)) /* Checks if the next move is not valid. */
			ghostDir[i] = rand() % 4;
		int xBeforeMove = ghost[i].body.getX();
		int yBeforeMove = ghost[i].body.getY();
		ghost[i].setDirection(ghostDir[i]);
		ghost[i].move(dontPrint);
		if (mode == 1)
			ghostsMoves.push_back(ghostDir[i]);

		if (board.boardArr[yBeforeMove][xBeforeMove] == '*' && mode != 3) {
			gotoxy(xBeforeMove, yBeforeMove);
			cout << '*';
		}
	}
	if (mode != 3)
		printCreatures();
}

int ThePacmanGame::checkCollisionGhost(const int dir, const int ghostNum) {
	switch (dir) {
	case UP:
		if (board.boardArr[ghost[ghostNum].body.getY() - 1][ghost[ghostNum].body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case DOWN:
		if (board.boardArr[ghost[ghostNum].body.getY() + 1][ghost[ghostNum].body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case LEFT:
		if (board.boardArr[ghost[ghostNum].body.getY()][ghost[ghostNum].body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case RIGHT:
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

void ThePacmanGame::GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir) {
	int xPlayer = player.body.getX(), yPlayer = player.body.getY();
	for (int i = 0; i < numOfGhosts; i++) {
		if ((xPlayer == ghost[i].body.getX()) && (yPlayer == ghost[i].body.getY())) {
			if (mode == 1) {
				gameMoves.push_back(numOfMoves);
			}
			else if (mode == 2 || mode == 3) {
				check();
			}
			/* If one of the ghosts eat pacman. */
			--life;
			flag = 0;
			start = 0;
			for (int k = 0; k < numOfGhosts; k++) {
				ghost[k].body.setXandY(ghost[k].body.getfirstX(), ghost[k].body.getfirstY());
			}
			player.body.setXandY(player.body.getfirstX(), player.body.getfirstY());
			if (mode != 3) {
				system("CLS");
				board.PrintBoard();
				printCreatures();
			}
			player.setDirection(4);
			dir = 4;
			for (int k = 0; k < numOfGhosts; k++) {
				ghost[k].setDirection(0);
				ghostDir[k] = 0;
			}
			if (mode != 3) {
				gotoxy(board.printx, board.printy);
				cout << "score: " << score << ' ' << "life: " << life;
				gotoxy(board.printx, board.printy + 1);
				cout << "Difficult Level: " << board.difficult + 1;
			}
			break; /* avoid from being eaten twice(if the ghosts are on the same spot) */
		}
	}

}

void ThePacmanGame::avoidTunnels(int ghostDir[]) {
	int ghostx[4];
	int ghosty[4];
	for (int i = 0; i < numOfGhosts; i++) {
		ghostx[i] = ghost[i].body.getX();
		ghosty[i] = ghost[i].body.getY();
		if (ghostx[i] == board.botR.getX())
			ghostDir[i] = LEFT;

		else if (ghostx[i] == board.topL.getX())
			ghostDir[i] = RIGHT;

		else if (ghosty[i] == board.botR.getY())
			ghostDir[i] = UP;

		else if (ghosty[i] == board.topL.getY())
			ghostDir[i] = DOWN;
	}
}

void ThePacmanGame::printCreatures() {
	if (mode != 3) {
		player.printBody(player.drawchar());
		for (int i = 0; i < numOfGhosts; i++) {
			ghost[i].printBody(ghost[i].drawchar());
		}
	}
}

void ThePacmanGame::movingThroughTunnel() {
	if (player.body.getY() == board.topL.getY()) {
		if (mode != 3) {
			gotoxy(player.body.getX(), player.body.getY());
			cout << ' ';
		}
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(player.body.getX(), board.botR.getY() - 1);
	}
	if (player.body.getY() == board.botR.getY()) {
		if (mode != 3) {
			gotoxy(player.body.getX(), player.body.getY());
			cout << ' ';
		}
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(player.body.getX(), board.topL.getY());
	}
	if (player.body.getX() == board.topL.getX()) {
		if (mode != 3) {
			gotoxy(player.body.getX(), player.body.getY());
			cout << ' ';
		}
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(board.botR.getX() - 1, player.body.getY());
	}
	if (player.body.getX() == board.botR.getX()) {
		if (mode != 3) {
			gotoxy(player.body.getX(), player.body.getY());
			cout << ' ';
		}
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(board.topL.getX(), player.body.getY());
	}
	if (mode != 3) {
		gotoxy(player.body.getX(), player.body.getY());
		cout << player.drawchar();
		gotoxy(board.printx, board.printy);
		cout << "score: " << score;
	}
}

vector<int> ThePacmanGame::shortestPath(char mat[][80], int rRow, int rCol, Point src, Point dest)
{
	int i = 0;
	/*stores the moves of the directions of cells*/
	int dRow[4] = { -1, 0, 0, 1 };
	int dCol[4] = { 0, -1, 1, 0 };

	int distance[25][80]; /*the distance of each cell from the source cell*/
	memset(distance, -1, sizeof distance);
	distance[src.getX()][src.getY()] = 0; /*distance of source cell is 0*/

	bool visited[25][80]; /*make a bool visited array*/
	memset(visited, false, sizeof visited);

	visited[src.getX()][src.getY()] = true; /*mark source cell as visited*/

	/* Create a queue for BFS*/
	queue<Node> q;

	Node s = { src, 0 }; /*distance of source cell is 0*/

	/* Enqueue source cell*/
	q.push(s);

	bool ok = false; /*if the destination is not reached*/

	while (!q.empty()) {
		Node curr = q.front();
		Point pt = curr.pt;
		i++;

		/*if we reached the destination, find the path*/
		if (pt.getX() == dest.getX() && pt.getY() == dest.getY()) {
			int xx = pt.getX(), yy = pt.getY();
			int dist = curr.dist;

			/*assign the distance of destination to the distance matrix*/
			distance[pt.getX()][pt.getY()] = dist;
			vector<int> pathmoves; /*stores the smallest path*/

			while (xx != src.getX() || yy != src.getY()) { /*continue until source is reached*/
				/*DOWN*/
				if (xx > 0 && distance[xx - 1][yy] == dist - 1) {
					pathmoves.push_back(DOWN);
					xx--;
				}
				/*UP*/
				if (xx < rRow - 1 && distance[xx + 1][yy] == dist - 1) {
					pathmoves.push_back(UP);
					xx++;
				}
				/*RIGHT*/
				if (yy > 0 && distance[xx][yy - 1] == dist - 1) {
					pathmoves.push_back(RIGHT);
					yy--;
				}
				/*LEFT*/
				if (yy < rCol - 1 && distance[xx][yy + 1] == dist - 1) {
					pathmoves.push_back(LEFT);
					yy++;
				}
				dist--;
			}

			/*reverse the backtracked path*/
			reverse(pathmoves.begin(), pathmoves.end());
			ok = true;
			return pathmoves;
		}

		q.pop(); /*pop the start of queue*/

		for (int i = 0; i < 4; i++) { /*explore all directions*/
			int row = pt.getX() + dRow[i];
			int col = pt.getY() + dCol[i];

			/*if the curr cell is valid, "visit" the cell*/
			if (board.isValid(row, col) && (mat[row][col] == '1' || mat[row][col] == 's'
				|| mat[row][col] == 'd') && !visited[row][col]) {
				visited[row][col] = true; /*mark the curr cell as visited*/
				Point po; /*enque the cell*/
				po.setXandY(row, col);
				Node adjCell = { po, curr.dist + 1 };
				q.push(adjCell);
				distance[row][col] = curr.dist + 1; /*update the distance*/
			}
		}
		if (i == 2000)
			break;
	}
	if (!ok) {   /*if the destination is not reachable*/
		vector<int> noPath;
		noPath.push_back(-1);
		return noPath;
	}
}

void ThePacmanGame::ghostMovementBest(const bool dontPrint) {
	Point pacman, currGhost;
	vector<int> path;
	int lastX, lastY;
	for (int i = 0; i < numOfGhosts; i++) {
		if (mode == 2 || mode == 3) {
			ghost[i].setDirection(ghostsMoves[ghostsMoves.size() - 1]);
			ghostsMoves.pop_back();
			lastX = ghost[i].body.getX();
			lastY = ghost[i].body.getY();
			ghost[i].move(dontPrint);
			if (board.boardArr[lastY][lastX] == '*' && mode == 2) {
				gotoxy(lastX, lastY);
				cout << '*';
			}
		}
		else {
			pacman.setXandY(player.body.getY(), player.body.getX());
			currGhost.setXandY(ghost[i].body.getY(), ghost[i].body.getX());
			path = shortestPath(board.mat, board.rowboard1, board.colboard1, currGhost, pacman);
			if (path[0] != -1) {
				ghost[i].setDirection(path[0]);
				lastX = ghost[i].body.getX();
				lastY = ghost[i].body.getY();
				if (mode == 1)
					ghostsMoves.push_back(path[0]);
				ghost[i].move(dontPrint);
				if (board.boardArr[lastY][lastX] == '*') {
					gotoxy(lastX, lastY);
					cout << '*';
				}
			}
			else if (mode == 1)
				ghostsMoves.push_back(-1); /*the ghost will not move*/


			board.mat[player.body.getY()][player.body.getX()] = '1';
			board.mat[ghost[i].body.getY()][ghost[i].body.getX()] = '1';
		}
	}
}

void ThePacmanGame::selectedMovmentDiff(int* ghostDir, int& countSteps, const bool dontPrint) {
	if (board.difficult == 0) {
		ghostMovementNovice(ghostDir, countSteps, dontPrint);
	}
	else if (board.difficult == 1) {
		ghostMovementGood(ghostDir, countSteps,dontPrint);
	}
	else if (board.difficult == 2) {
		ghostMovementBest(dontPrint);
	}
	ghostEatFruit();
		if (fruit.HoldTime() == 0) {
			initFruit();
			fruit.setFruitOn(1);
		}
		if (fruit.LifeTime() != 0) {
			fruitMovment(dontPrint);
			fruit.runningTime();
		}
		else {
			fruit.setFruitOn(0);
			if (mode != 3) {
				gotoxy(fruit.body.getX(), fruit.body.getY());
				cout << board.boardArr[fruit.body.getY()][fruit.body.getX()];
			}
			fruit.holdingTime();
		}
	ghostEatFruit();

}

void ThePacmanGame::settings() {
	system("CLS");
	cout << "********************" << endl;
	cout << "******SETTINGS******" << endl;
	cout << "********************" << endl << endl;
	cout << "1. To Change The Difficulty Of The Game Please Press 1." << endl;
	cout << "2. To Change The Speed Of The Game Please Press 2." << endl;
	cout << "3. If You Would Like To Enter Your Own Game Board Please Select 3." << endl;
	cout << "3. To Return Please Press Any Other Key." << endl;
	char choice = '0';

	choice = _getch();

	if (choice != '1' && choice != '2' && choice != '3')
		choice = '0';
	else if (choice == '1')
		chooseLevel();
	else if (choice == '2')
		selectGameSpeed();
	else if (choice == '3') {
		system("CLS");
		boardNum = -1;
		board.boardname = "";
		score = 0;
		init();
	}
}

void ThePacmanGame::ghostMovementGood(int* ghostDir, int& countMovment, const bool dontPrint) {
	if (countMovment > 14) {
		ghostMovementNovice(ghostDir, countMovment, dontPrint);
	}
	else
		ghostMovementBest(dontPrint);

	if (countMovment > 20)
		countMovment = 0;
}

void ThePacmanGame::selectGameSpeed() {
	system("CLS");
	cout << "********************" << endl;
	cout << "********SPEED*******" << endl;
	cout << "********************" << endl << endl;
	char choice = '0';

	while (choice == '0') {
		cout << "For Slow Game Please Select 1." << endl;
		cout << "For Moderate Game Please Select 2." << endl;
		cout << "For Fast Game Please Select 3." << endl;
		choice = _getch();

		if (choice != '1' && choice != '2' && choice != '3')
			choice = '0';
		if (choice == '1') {
			sleepTime = 350;
			system("CLS");
			cout << "Speed Set To Slow!";
			Sleep(1500);
		}
		if (choice == '2') {
			system("CLS");
			cout << "Speed Set To Moderate!";
			sleepTime = 250;
			Sleep(1500);
		}
		if (choice == '3') {
			system("CLS");
			cout << "Speed Set To Fast!";
			sleepTime = 150;
			Sleep(1500);
		}
	}
}

void ThePacmanGame::initFruit() {
	if (mode == 1) {
		fruit.initRandNum();
		fruit.setFigure(fruit.drawchar());
		fruit.setHold(40);
		fruit.setLife(60);
		int i = rand() % board.posForFruit.size();
		fruit.body.setXandY(board.posForFruit[i].getX(), board.posForFruit[i].getY());
		fruitMoves.push_back(fruit.addScore());
		fruitMoves.push_back(fruit.body.getY());
		fruitMoves.push_back(fruit.body.getX());
	}
	else if (mode == 2 || mode == 3) {
		fruit.initRandNum(fruitMoves[fruitMoves.size() - 1]);
		fruitMoves.pop_back();
		int y = fruitMoves[fruitMoves.size() - 1];
		fruitMoves.pop_back();
		int x = fruitMoves[fruitMoves.size() - 1];
		fruitMoves.pop_back();
		fruit.setFigure(fruit.drawchar());
		fruit.setHold(40);
		fruit.setLife(60);
		fruit.body.setXandY(x, y);
	}
}

void ThePacmanGame::fruitMovment(const bool dontPrint) {
	int dir;
	avoidTunnelsFruit();
	while (!checkCollisionFruit()) { /* Checks if the next move is not valid. */
		dir = rand() % 4;
		fruit.setDirection(dir);
	}
	dir = fruit.getDir();
	int xBeforeMove = fruit.body.getX();
	int yBeforeMove = fruit.body.getY();
	if (mode == 2 || mode == 3) {
			dir = fruitMoves[fruitMoves.size() - 1];
			fruitMoves.pop_back();
			fruit.setDirection(dir);
		
	}
	fruit.move(dontPrint);
	if (mode == 1)
		fruitMoves.push_back(dir);

	if (board.boardArr[yBeforeMove][xBeforeMove] == '*' && mode != 3) {
		gotoxy(xBeforeMove, yBeforeMove);
		cout << '*';
	}
}

void ThePacmanGame::avoidTunnelsFruit() {
	if (fruit.body.getX() == board.botR.getX())
		fruit.setDirection(LEFT);

	else if (fruit.body.getX() == board.topL.getX())
		fruit.setDirection(RIGHT);

	else if (fruit.body.getY() == board.botR.getY())
		fruit.setDirection(UP);

	else if (fruit.body.getY() == board.topL.getY())
		fruit.setDirection(DOWN);

}

int ThePacmanGame::checkCollisionFruit() {
	switch (fruit.direction) {
	case UP:
		if (board.boardArr[fruit.body.getY() - 1][fruit.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case DOWN:
		if (board.boardArr[fruit.body.getY() + 1][fruit.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case LEFT:
		if (board.boardArr[fruit.body.getY()][fruit.body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case RIGHT:
		if (board.boardArr[fruit.body.getY()][fruit.body.getX() + 1] == char(178))
			return 0;
		else
			return 1;

		break;
	default:
		return 0;
		break;
	}

}

void ThePacmanGame::pacmanEatFruit() {
	if (fruit.fruitOn() == 1) {
		if (player.body.getX() == fruit.body.getX() && player.body.getY() == fruit.body.getY()) {
			score += fruit.addScore();
			fruit.setFruitOn(0);
			fruit.setHold(40);
			fruit.setLife(0);
			if (mode != 3) {
				gotoxy(board.printx, board.printy);
				cout << "score: " << score;
			}
		}
	}
	printCreatures();
}

void ThePacmanGame::ghostEatFruit() {
	if (fruit.fruitOn() == 1) {
		for (int i = 0; i < numOfGhosts; i++) {
			if (ghost[i].body.getX() == fruit.body.getX() && ghost[i].body.getY() == fruit.body.getY()) {
				fruit.setFruitOn(0);
				fruit.setHold(40);
				fruit.setLife(0);
			}
		}
	}
	printCreatures();
}

void ThePacmanGame::saveMode() {
	string fileName = board.boardname;
	for (int k = 0; k < 6; k++)
		fileName.pop_back();

	fileName += "steps";
	ofstream myReadFile;
	myReadFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	reverse(pacmanMoves.begin(), pacmanMoves.end());
	size_t size = pacmanMoves.size();
	for (int i = (int)size - 1; i >= 0; i--) {
		myReadFile << pacmanMoves[i];
		myReadFile << ' ';
		pacmanMoves.pop_back();
	}
	myReadFile << 99;
	myReadFile << ' ';
	reverse(ghostsMoves.begin(), ghostsMoves.end());
	size = ghostsMoves.size();
	for (int i = (int)size - 1; i >= 0; i--) {
		myReadFile << ghostsMoves[i];
		myReadFile << ' ';
		ghostsMoves.pop_back();
	}
	myReadFile << 99;
	myReadFile << ' ';
	reverse(fruitMoves.begin(), fruitMoves.end());
	size = fruitMoves.size();
	for (int i = (int)size - 1; i >= 0; i--) {
		myReadFile << fruitMoves[i];
		myReadFile << ' ';
		fruitMoves.pop_back();
	}
	myReadFile.close();
	for (int k = 0; k < 5; k++)
		fileName.pop_back();
	fileName += "result";
	myReadFile.open(fileName, std::ofstream::out | std::ofstream::trunc);
	reverse(gameMoves.begin(), gameMoves.end());
	size = gameMoves.size();
	for (int i = (int)size - 1; i >= 0; i--) {
		myReadFile << gameMoves[i];
		myReadFile << ' ';
		gameMoves.pop_back();
	}
	myReadFile.close();

}
void ThePacmanGame::getInputs() {
	int integer;
	string fileName = board.boardname;
	for (int k = 0; k < 6; k++)
		fileName.pop_back();

	fileName += "steps";
	ifstream myReadFile;
	myReadFile.open(fileName);
	myReadFile >> integer;
	while (integer != 99) {
		pacmanMoves.push_back(integer);
		myReadFile >> integer;
	}
	do {
		myReadFile >> integer;
		if (integer != 99)
			ghostsMoves.push_back(integer);
	} while (integer != 99);
	do {
		myReadFile >> integer;
		if (integer != 99)
			fruitMoves.push_back(integer);
	} while (!myReadFile.eof());
	myReadFile.close();
	for (int k = 0; k < 5; k++)
		fileName.pop_back();
	fileName += "result";
	myReadFile.open(fileName);
	while (!myReadFile.eof()) {
		myReadFile >> integer;
		gameMoves.push_back(integer);
	}
	gameMoves.pop_back();
	myReadFile.close();
}

void ThePacmanGame::check() {
	if (mode == 2 || mode == 3) {
		if (gameMoves[gameMoves.size() - 1] != numOfMoves && gameMoves[gameMoves.size() - 1] != (numOfMoves - 1)
			&& gameMoves[gameMoves.size() - 1] != (numOfMoves + 1)) {
			gameMoves.pop_back();
			system("CLS");
			cout << "test faild!";
			exit(0);
		}
		gameMoves.pop_back();
	}
}

void ThePacmanGame::makeEmptyVec() {
	while (!pacmanMoves.empty())
		pacmanMoves.pop_back();

	while (!ghostsMoves.empty())
		ghostsMoves.pop_back();

	while (!fruitMoves.empty())
		fruitMoves.pop_back();

	while (!gameMoves.empty())
		gameMoves.pop_back();
}

void ThePacmanGame::EndGameMode3() {
	if (mode == 3) {
		system("CLS");
		cout << "Test Passed!" << endl;
		exit(0);
	}
}

void ThePacmanGame::printWaitingTime() {
	int i = numOfMoves % 30;
	if (0 <= i && i <= 9) {
		cout << "Calculating." << endl;
		gotoxy(12, 0);
		cout << "  ";
		gotoxy(0, 0);
	}
	else if (10 <= i && i <= 19) {
		cout << "Calculating.." << endl;
		gotoxy(13, 0);
		cout << " ";
		gotoxy(0, 0);
	}
	else {
		cout << "Calculating..." << endl;
		gotoxy(0, 0);
	}
}

void ThePacmanGame::setSpeedInLoad() {
	if (mode == 3)
		sleepTime = 0;
	if (mode == 2)
		sleepTime = 70;
}