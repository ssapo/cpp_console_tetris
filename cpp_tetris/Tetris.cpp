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

	constexpr int width = GAME_WIDTH;
	constexpr int height = GAME_HEIGHT;

	board = std::make_unique<Board>(width, height);
	if (nullptr == board)
	{
		return false;
	}

	renderer->add(0, board.get());





	updater->add(0, this);
	return true;
}

void Tetris::update(float delta) noexcept
{

}

