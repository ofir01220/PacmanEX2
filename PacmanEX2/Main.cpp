#include <windows.h>
#include <iostream>

#include "ThePacmanGame.h"

void inputFromCMDOrNot(ThePacmanGame& game, const int argc, const char** argv);
void playGame(ThePacmanGame& game);

int main(int argc, char** argv) {
	ThePacmanGame game;
	inputFromCMDOrNot(game, argc, argv);
	playGame(game);
}

void inputFromCMDOrNot(ThePacmanGame& game, const int argc, const char** argv) {
	if (argc == 1) {
		game.setmode(0);
	}
	else if (argc == 2) {
		if (!strcmp(argv[1], "-load"))
			game.setmode(2);

		else if (!strcmp(argv[1], "-save"))
			game.setmode(1);
	}
	else if (argc == 3) {
		if (!strcmp(argv[1], "-load")) {
			game.setmode(2);
			if (!strcmp(argv[2], "[-silent]"))
				game.setmode(3);
		}
		else if (!strcmp(argv[1], "-save"))
			game.setmode(1);
	}
	else if (argc > 3) {
		cout << "Wrong input!" << endl;
		exit(0);
	}
}

void playGame(ThePacmanGame& game) {
	int i = 0;
	int mode = game.getGameMode();
	hideCursor();
	while (i == 0) {
		if (mode != 2 && mode != 3) {
			game.mainMenu();
			system("CLS");
		}
		game.init();
		game.run();
	}
}