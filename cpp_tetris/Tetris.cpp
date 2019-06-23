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
			if (!cells[index])
			{
				return false;
			}

			renderer->add(1, index, cells[index].get());
		}
	}

	//auto i_block = std::make_unique<BlockObject>(P(0, 0)
	//	, new std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
	//	);

	//auto j_block = std::make_unique<BlockObject>(P(0, 0)
	//	, new std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
	//	);

	//auto l_block = std::make_unique<BlockObject>(P(0, 0)
	//	, new std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
	//	);

	dic_block_rot['o'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(0, 0), P(-1, 0), P(-1, 1), P(0, 1)}
			, std::vector<Point>{P(0, 0), P(-1, 0), P(-1, 1), P(0, 1)}
			, std::vector<Point>{P(0, 0), P(-1, 0), P(-1, 1), P(0, 1)}
			, std::vector<Point>{P(0, 0), P(-1, 0), P(-1, 1), P(0, 1)}
		}
	);
	blocks['o'] = std::make_unique<BlockObject>(P(0, 0), dic_block_rot['o'].get());

	/*auto s_block = std::make_unique<BlockObject>(P(0, 0)
		, std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
		);

	auto t_block = std::make_unique<BlockObject>(P(0, 0)
		, std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
		);

	auto z_block = std::make_unique<BlockObject>(P(0, 0)
		, std::array<std::vector<Point>, Constant::COUNT_ROTATION>()
		);*/

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

		update_sec(sec_timer);
	}
}

void Tetris::update_sec(float sec) noexcept
{

}

TETRIS_END