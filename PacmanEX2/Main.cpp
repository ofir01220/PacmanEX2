#include <windows.h>
#include <iostream>
using namespace std;

#include "ThePacmanGame.h"

int main() {
	ThePacmanGame game;
	hideCursor();
	int i = 0;
	while (i == 0) {
		game.mainMenu();
		system("CLS");
		game.init();
		game.run();
	}
}