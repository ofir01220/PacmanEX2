#include "ThePacmanGame.h"

void ThePacmanGame::init()
{
	player.setArrowKeys("wxadsWXADS");
	player.setFigure((char)002);
	board.activateBoard(player, ghost, this->numOfGhosts,boardNum);
	for(int i = 0; i < numOfGhosts; i++)
		ghost[i].setFigure((char)234);
	player.initilizeCrumbs(board.breadCrumbs);
	board.PrintBoard();
	printCreatures();
	board.initMat();
}
void ThePacmanGame::run() 
{
	char key = 0;
	int dir = UP, start = FALSE, life = 3, lastDir, ghostDelay = FALSE, ghostDir[4] = { 0,0 }, flag = 0, countMovment = 0;
	printCreatures();
	gotoxy(board.printx, board.printy);
	cout << "score: " << score << ' ' << "life: " << life;
	gotoxy(board.printx, board.printy + 1);
	cout << "Difficult Level: " << board.difficult + 1;
	do {
		lastDir = dir; /*if the player selects a direction that will hit a wall, we avoid that direction and continue on the last direction (see lines 29-31)*/
		if (_kbhit())
		{
			key = _getch();
			if ((player.getDirection(key)) != -1)
				ifPause = 1;
			checkValidKey(key, dir, lastDir, life, flag); /*check if the pressed key is a valid key(move or pause)*/
		}
		start = checkCollisionPacman(dir);
		if (!start) {
			dir = lastDir;
			start = checkCollisionPacman(dir);
		}
		player.setDirection(dir);
		if (start && ifPause) {
			player.move();
			movingThroughTunnel();
			yummy(life); /*checks if the pacman ate a crumb.*/
			flag = 1;
		}
		if (flag == 1) /*starts the sleep function only if the game starts*/
			Sleep(sleepTime);

		GhostEatPacman(life, flag, start, dir, ghostDir);
		pacmanEatFruit();
		if ((ghostDelay == TRUE) && (flag)) { /*to make the ghost go 2X slower than the pacman*/
			selectedMovmentDiff(ghostDir, countMovment);
			countMovment++;
			ghostDelay = FALSE;
		}
		else
			ghostDelay = TRUE;
		GhostEatPacman(life, flag, start, dir, ghostDir);
		pacmanEatFruit();
	} while (endGameConditions(life, flag));

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

void ThePacmanGame::chooseLevel() {
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

void ThePacmanGame::pause(int& dir, int& life, int& lastDir, int& flag) {
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

int ThePacmanGame::endGameConditions(const int life, int &flag) {
	if (player.Crumbs() == 0 && (boardNum == board.numOfBoards  || boardNum == -1)) { /*max point.*/
		winGame();
		score = 0;
		board.difficult = 0;
		flag = 0;
		boardNum = 1;
		ifPause = 0;
		return 0;
	}
	else if (player.Crumbs() == 0) {
		boardNum++;
		if(board.difficult != 2)
			board.difficult = board.difficult + 1;
		system("CLS");
		init();
		score = 0;
		flag = 0;
	}
	else if (life == 0) {
		lostGame();
		boardNum = 1;
		score = 0;
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

void ThePacmanGame::yummy(int life) {
	if (board.boardArr[player.body.getY()][player.body.getX()] == '*') { /*if the user ate crumb.*/
		board.boardArr[player.body.getY()][player.body.getX()] = ' '; /*we delete the crumb from the board*/
		score++;
		player.eatCrumb();
		gotoxy(board.printx, board.printy);
		cout << "score: " << score << ' ' << "life: " << life;
		gotoxy(board.printx, board.printy + 1);
		cout << "Difficult Level: " << board.difficult + 1;
	}
}

void ThePacmanGame::checkValidKey(int key, int& dir, int& lastDir, int& life, int& flag) {
	if (key == ESC)
		pause(dir, life, lastDir, flag);


	if ((player.getDirection(key)) != -1)
		dir = player.getDirection(key);
}

void ThePacmanGame::ghostMovementNovice(int* ghostDir, int& countMovment) {

	if (countMovment == 21) {
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

void ThePacmanGame::GhostEatPacman(int& life, int& flag, int& start, int& dir, int* ghostDir) {
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
			gotoxy(board.printx, board.printy);
			cout << "score: " << score << ' ' << "life: " << life;
			gotoxy(board.printx, board.printy + 1);
			cout << "Difficult Level: " << board.difficult + 1;
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
	player.printBody((char)002);
	for (int i = 0; i < numOfGhosts; i++) {
		ghost[i].printBody((char)234);
	}
}

void ThePacmanGame::movingThroughTunnel() {
	if (player.body.getY() == board.topL.getY()) {
		gotoxy(player.body.getX(), player.body.getY());
		cout << ' ';
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(player.body.getX(), board.botR.getY() - 1);
	}
	if (player.body.getY() == board.botR.getY()) {
		gotoxy(player.body.getX(), player.body.getY());
		cout << ' ';
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(player.body.getX(), board.topL.getY());
	}
	if (player.body.getX() == board.topL.getX()) {
		gotoxy(player.body.getX(), player.body.getY());
		cout << ' ';
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(board.botR.getX() - 1, player.body.getY());
	}
	if (player.body.getX() == board.botR.getX()) {
		gotoxy(player.body.getX(), player.body.getY());
		cout << ' ';
		if (board.boardArr[player.body.getY()][player.body.getX()] == '*') {
			score++;
			player.eatCrumb();
			board.boardArr[player.body.getY()][player.body.getX()] = ' ';
		}
		player.body.setXandY(board.topL.getX(), player.body.getY());
	}
	gotoxy(player.body.getX(), player.body.getY());
	cout << (char)2;
	gotoxy(board.printx, board.printy);
	cout << "score: " << score;
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
		return (vector<int>)-1;
}

void ThePacmanGame::ghostMovementBest() {
	Point pacman, currGhost;
	vector<int> path;
	int lastX, lastY;
	for (int i = 0; i < numOfGhosts; i++) {
		pacman.setXandY(player.body.getY(), player.body.getX());
		currGhost.setXandY(ghost[i].body.getY(), ghost[i].body.getX());
		path = shortestPath(board.mat, board.rowboard1, board.colboard1, currGhost, pacman);
		if (path[0] != -1) {
			ghost[i].setDirection(path[0]);
			lastX = ghost[i].body.getX();
			lastY = ghost[i].body.getY();
			ghost[i].move();
			if (board.boardArr[lastY][lastX] == '*') {
				gotoxy(lastX, lastY);
				cout << '*';
			}
		}
		
		board.mat[player.body.getY()][player.body.getX()] = '1';
		board.mat[ghost[i].body.getY()][ghost[i].body.getX()] = '1';
	}
}

void ThePacmanGame::selectedMovmentDiff(int* ghostDir,int &countSteps) {
	if (board.difficult == 0){
		ghostMovementNovice(ghostDir, countSteps);
	}
	else if (board.difficult == 1) {
		ghostMovementGood(ghostDir, countSteps);
	}
	else if (board.difficult == 2) {
		ghostMovementBest();
	}
	ghostEatFruit();
	if (fruit.HoldTime() == 0) {
		initFruit();
		fruit.setFruitOn(1);
	}
	if (fruit.LifeTime() != 0) {
		fruitMovment();
		fruit.runningTime();
	}
	else {
		fruit.setFruitOn(0);
		gotoxy(fruit.body.getX(), fruit.body.getY());
		cout << board.boardArr[fruit.body.getY()][fruit.body.getX()];
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
		init();
	}
}

void ThePacmanGame::ghostMovementGood(int* ghostDir, int& countMovment) {
	if (countMovment > 14) {
		ghostMovementNovice(ghostDir, countMovment);
	}
	else
		ghostMovementBest();

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
	fruit.initRandNum();
	fruit.setFigure(fruit.addScore() + '0');
	fruit.setHold(40);
	fruit.setLife(60);
	int i = rand() % board.posForFruit.size();
	fruit.body.setXandY(board.posForFruit[i].getX(), board.posForFruit[i].getY());
}

void ThePacmanGame::fruitMovment() {
	avoidTunnelsFruit();
	while (!checkCollisionFruit()) /* Checks if the next move is not valid. */
		fruit.setDirection(rand() % 4);
		int xBeforeMove = fruit.body.getX();
		int yBeforeMove = fruit.body.getY();
		fruit.move();

		if (board.boardArr[yBeforeMove][xBeforeMove] == '*') {
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
	case 0: // UP
		if (board.boardArr[fruit.body.getY() - 1][fruit.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 1: // DOWN
		if (board.boardArr[fruit.body.getY() + 1][fruit.body.getX()] == char(178))
			return 0;
		else
			return 1;

		break;
	case 2: // LEFT
		if (board.boardArr[fruit.body.getY()][fruit.body.getX() - 1] == char(178))
			return 0;
		else
			return 1;

		break;
	case 3: // (3)- RIGHT
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
			fruit.setHold(40);
			fruit.setLife(0);
			gotoxy(board.printx, board.printy);
			cout << "score: " << score;
		}
	}
}

void ThePacmanGame::ghostEatFruit() {
	if (fruit.fruitOn() == 1) {
		for (int i = 0; i < numOfGhosts; i++){
			if (ghost[i].body.getX() == fruit.body.getX() && ghost[i].body.getY() == fruit.body.getY()) {
				fruit.setHold(40);
				fruit.setLife(0);
			}
		}
	}
	printCreatures();
}