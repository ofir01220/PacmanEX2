#include <windows.h>
#include <iostream>

#include "ThePacmanGame.h"

int main(int argc, char** argv) {
	ThePacmanGame game;
	if (argc > 1) {
		if (!strcmp(argv[1], "-load")) {
			/**/
		}
		if (!strcmp(argv[1], "-save")) {
			game.setmode(1);

		}
		if (!strcmp(argv[2], "-silent")) {
			/**/
		}
	}
			

	hideCursor();
	int i = 0;
	while (i == 0) {
		game.mainMenu();
		system("CLS");
		game.init();
		game.run();
	}
}