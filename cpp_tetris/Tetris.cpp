#include "Tetris.h"
#include "Game.h"
#include "Board.h"

Tetris::Tetris()
{

}

Tetris::~Tetris()
{

}

bool Tetris::initialize(Game* game)
{
	int width = Game::console_width;
	int height = Game::console_height;

	board = std::make_unique<Board>(width, height);

	return true;
}

