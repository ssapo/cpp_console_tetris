#include "Tetris.h"

Tetris::Tetris(const int width, const int height)
	: board(std::make_unique<Board>(width, height))
{

}

Tetris::~Tetris()
{

}

