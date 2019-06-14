#include "Tetris.h"
#include "Game.h"
#include "Board.h"
#include "Renderer.h"
#include "Updater.h"

Tetris::Tetris()
{

}

Tetris::~Tetris()
{

}

bool Tetris::initialize()
{
	auto renderer = get_game()->get_renderer();
	auto updater = get_game()->get_updater();

	constexpr int width = Game::console_width;
	constexpr int height = Game::console_height;

	board = std::make_unique<Board>(width, height);
	if (nullptr == board)
	{
		return false;
	}

	renderer->add(0, board.get());
	updater->add(0, board.get());



	return true;
}

