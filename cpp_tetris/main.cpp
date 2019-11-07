#include "Tetris.h"
#include "Game.h"

USING_TETRIS

int main()
{
	Tetris tetris_rogic;
	Game excuter(tetris_rogic);

	return excuter.main();
}