#include "Game.h"

int main(int argc, char *argv[]) {

	Game *game = new Game();

	game->setup();
	game->start();

	return 0;
}