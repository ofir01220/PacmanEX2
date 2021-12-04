#include "ThePacmanGame.h"

void ThePacmanGame::init()
{
	player.setArrowKeys("wxadsWXADS");
	player.setFigure((char)002);
	board.activateBoard(player, ghost, this->numOfGhosts);
	for(int i = 0; i < numOfGhosts; i++)
		ghost[i].setFigure((char)234);
	board.PrintBoard();
	board.initMat();
}
void ThePacmanGame::run()
{
	char key = 0;
	int dir = UP, start = FALSE, score = 0, life = 3, lastDir, ghostDelay = FALSE, ghostDir[4] = { 0,0 }, flag = 0, countMovment = 0;
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
			movingThroughTunnel();
			yummy(score, life); /*checks if the pacman ate a crumb.*/
			flag = 1;
		}
		if (flag == 1) /*starts the sleep function only if the game starts*/
			Sleep(200);

		GhostEatPacman(life, flag, start, dir, ghostDir, score);
		if ((ghostDelay == TRUE) && (flag)) { /*to make the ghost go 2X slower than the pacman*/
			//ghostMovementNovice(ghostDir, countMovment);
			ghostMovementBest();
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
		cout << "****************" << endl;
		cout << "*****PACMAN*****" << endl;
		cout << "****************" << endl << endl;
		cout << "To Start The Game Please Press 1" << endl;
		cout << "For Instructions Please press 8" << endl;
		cout << "If You Wish To Exit Please Press 9" << endl;
		choice = _getch();
		if (choice != '1' && choice != '8' && choice != '9')
			choice = '0';

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
	cout << "7. Have FUN don't DIE!." << endl << endl;
	cout << "If you wish to return to the main menu please press any key." << endl;
}

void ThePacmanGame::chooseLevel() {
	system("CLS");
	cout << "********************" << endl;
	cout << "****CHOOSE LEVEL****" << endl;
	cout << "********************" << endl << endl;
	cout << "1. To play EASY mode, press 1." << endl;
	cout << "2. To play MEDIUM mode, press 2." << endl;
	cout << "3. To play HARD mode, press 3." << endl;
	cout << "If you wish to return to the main menu please press any other key." << endl;
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
		board.activateBoard(player, ghost, this->numOfGhosts);
		system("CLS");
		mainMenu();
	}
	if (trash == 'r' || trash == 'R') {/*RESTART*/
		score = 0;
		life = 3;
		dir = lastDir = 0;
		flag = 0;
		system("CLS");
		init(); /*to init the game from the begining */
	}
	else {
		system("CLS");
		board.PrintBoard();
		printCreatures();
	}
	gotoxy(0, 24);
	cout << "score: " << score << ' ' << "life: " << life;
}

int ThePacmanGame::endGameConditions(const int score, const int life) {
	if (score == board.breadCrumbs) { /*max point.*/
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

	if (countMovment == 20) {
		ghostDir[0] = rand() % 4;
		ghostDir[1] = rand() % 4;
		ghostDir[2] = rand() % 4;
		ghostDir[3] = rand() % 4;
		countMovment = 0;
	}
	avoidTunnels(ghostDir);
	for (int i = 0; i < numOfGhosts; i++) {
		while (!checkCollisionGhost(ghostDir[i], i)) /* Checks if the next move is not valid. */
			ghostDir[i] = rand() % 4;
		int xBeforeMove = ghost[i].body.getX();
		int yBeforeMove = ghost[i].body.getY();
		ghost[i].setDirection(ghostDir[i]);
		ghost[i].move();

		if (board.boardArr[yBeforeMove][xBeforeMove] == '*') {
			gotoxy(xBeforeMove, yBeforeMove);
			cout << '*';
		}
	}
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
	int xPlayer = player.body.getX(), yPlayer = player.body.getY();
	for (int i = 0; i < numOfGhosts; i++) {
		if ((xPlayer == ghost[i].body.getX()) && (yPlayer == ghost[i].body.getY())) {
			/* If one of the ghosts eat pacman. */
				--life;
			flag = 0;
			start = 0;
			for (int k = 0; k < numOfGhosts; k++) {
				ghost[k].body.setXandY(ghost[k].body.getfirstX(), ghost[k].body.getfirstY());
			}
			player.body.setXandY(player.body.getfirstX(), player.body.getfirstY());
			system("CLS");
			board.PrintBoard();
			printCreatures();
			player.setDirection(0);
			for (int k = 0; k < numOfGhosts; k++) {
				ghost[k].setDirection(0);
				dir = ghostDir[k] = 0;
			}
			break; /* avoid from being eaten twice(if the ghosts are on the same spot) */
		}
	}
	gotoxy(0, 24);
	cout << "score: " << score << ' ' << "life: " << life;
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

void ThePacmanGame::printCreatures() {
	player.printBody((char)002);
	for (int i = 0; i < numOfGhosts; i++) {
		ghost[i].printBody((char)234);
	}
}

void ThePacmanGame::movingThroughTunnel() {
	if (player.body.getY() == board.topL.getY()) {
		gotoxy(player.body.getY(), player.body.getX());
		cout << ' ';
		player.body.setXandY(player.body.getX(), board.botR.getY() - 1);
	}
	if (player.body.getY() == board.botR.getY()) {
		gotoxy(player.body.getY(), player.body.getX());
		cout << ' ';
		player.body.setXandY(player.body.getX(), board.topL.getY() + 1);
	}
	if (player.body.getX() == board.topL.getX()) {
		gotoxy(player.body.getY(), player.body.getX());
		cout << ' ';
		player.body.setXandY(board.botR.getX() - 1, player.body.getY());
	}
	if (player.body.getX() == board.botR.getX()) {
		gotoxy(player.body.getY(), player.body.getX());
		cout << ' ';
		player.body.setXandY(board.botR.getX() + 1, player.body.getY());
	}
}

vector<int> ThePacmanGame::shortestPath(char mat[][80],int rRow, int rCol, Point src, Point dest)
{
	//stores the moves of the directions of cells
	int dRow[4] = { -1, 0, 0, 1 };
	int dCol[4] = { 0, -1, 1, 0 };

	int distance[25][80]; //the distance of each cell from the source cell
	memset(distance, -1, sizeof distance);
	distance[src.getX()][src.getY()] = 0; //distance of source cell is 0

	bool visited[25][80]; //make a bool visited array
	memset(visited, false, sizeof visited);

	visited[src.getX()][src.getY()] = true; //mark source cell as visited

	// Create a queue for BFS
	queue<Node> q;

	Node s = { src, 0 }; //distance of source cell is 0

	// Enqueue source cell
	q.push(s);

	bool ok = false; //if the destination is not reached

	while (!q.empty()) {
		Node curr = q.front();
		Point pt = curr.pt;

		//if we reached the destination, find the path
		if (pt.getX() == dest.getX() && pt.getY() == dest.getY()) {
			int xx = pt.getX(), yy = pt.getY();
			int dist = curr.dist;

			//assign the distance of destination to the distance matrix
			distance[pt.getX()][pt.getY()] = dist;
			vector<int> pathmoves; //stores the smallest path

			while (xx != src.getX() || yy != src.getY()) { //continue until source is reached
				//DOWN
				if (xx > 0 && distance[xx - 1][yy] == dist - 1) {
					pathmoves.push_back(DOWN);
					xx--;
				}
				//UP
				if (xx < rRow - 1 && distance[xx + 1][yy] == dist - 1) {
					pathmoves.push_back(UP);
					xx++;
				}
				//RIGHT
				if (yy > 0 && distance[xx][yy - 1] == dist - 1) {
					pathmoves.push_back(RIGHT);
					yy--;
				}
				//LEFT
				if (yy < rCol - 1 && distance[xx][yy + 1] == dist - 1) {
					pathmoves.push_back(LEFT);
					yy++;
				}
				dist--;
			}

			//reverse the backtracked path
			reverse(pathmoves.begin(), pathmoves.end());
			ok = true;
			return pathmoves;
		}

		q.pop(); //pop the start of queue

		for (int i = 0; i < 4; i++) { //explore all directions
			int row = pt.getX() + dRow[i];
			int col = pt.getY() + dCol[i];

			//if the curr cell is valid, "visit" the cell
			if (board.isValid(row, col) && (mat[row][col] == '1' || mat[row][col] == 's'
				|| mat[row][col] == 'd') && !visited[row][col]) {
				visited[row][col] = true; //mark the curr cell as visited
				Point po; //enque the cell
				po.setXandY(row, col);
				Node adjCell = { po, curr.dist + 1 };
				q.push(adjCell);
				distance[row][col] = curr.dist + 1; //update the distance
			}
		}
	}

	if (!ok) //if the destination is not reachable
		return (vector<int>)0;
}

void ThePacmanGame::ghostMovementBest() {
	Point pacman, currGhost;
	vector<int> path;
	int lastX, lastY;
	for (int i = 0; i < numOfGhosts; i++) {
		pacman.setXandY(player.body.getY(), player.body.getX());
		currGhost.setXandY(ghost[i].body.getY(), ghost[i].body.getX());
		path = shortestPath(board.mat, board.rowboard1, board.colboard1, currGhost, pacman);
		ghost[i].setDirection(path[0]);
		lastX = ghost[i].body.getX();
		lastY = ghost[i].body.getY();
		ghost[i].move();
		if (board.boardArr[lastY][lastX] == '*') {
			gotoxy(lastX, lastY);
			cout << '*';
		}
		board.mat[player.body.getY()][player.body.getX()] = '1';
		board.mat[ghost[i].body.getY()][ghost[i].body.getX()] = '1';
	}
}


