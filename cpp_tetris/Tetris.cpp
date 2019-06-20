#include "Tetris.h"
#include "Game.h"
#include "Board.h"
#include "Renderer.h"
#include "Updater.h"
#include "Cell.h"
#include "BlockObject.h"
#include <iostream>

TETRIS_START

Tetris::Tetris()
	: sec_timer(0.0f)
	, frame_timer(0.0f)
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

	board = std::make_unique<Board>(width, height, Renderer::TextColor::red);
	if (nullptr == board)
	{
		return false;
	}

	renderer->add(0, 0, board.get());

	for (int y = 0; y < CELL_HEIGHT; ++y)
	{
		for (int x = 0; x < CELL_WIDTH; ++x)
		{
			int index = (y * CELL_WIDTH) + x;

			cells[index] = std::make_unique<Cell>(x + 1, y + 1, true, Renderer::TextColor::gray);
			renderer->add(1, index, cells[index].get());
		}
	}

	updater->add(0, this);
	return true;
}

void Tetris::update(float delta) noexcept
{
	//std::cout << delta << std::endl;
	frame_timer += delta;
	if (frame_timer >= TIME_SEC)
	{
		frame_timer = 0.0f;
		sec_timer += TIME_SEC;
	}

}

TETRIS_END