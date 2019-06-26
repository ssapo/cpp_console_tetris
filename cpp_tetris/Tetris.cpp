#include "Tetris.h"
#include "Game.h"
#include "Board.h"
#include "Renderer.h"
#include "Updater.h"
#include "Cell.h"
#include "BlockObject.h"

TETRIS_START

Tetris::Tetris()
	: sec_timer(0.0f)
	, frame_timer(0.0f)
{

}

Tetris::~Tetris()
{

}

bool Tetris::initialize() noexcept
{
	auto renderer = get_game()->get_renderer();
	auto updater = get_game()->get_updater();

	constexpr int width = GAME_WIDTH;
	constexpr int height = GAME_HEIGHT;

	board = std::make_unique<Board>(width, height, Color::red);
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

			cells[index] = std::make_unique<Cell>(x + 1, y + 1, true, Color::gray);
			if (!cells[index])
			{
				return false;
			}

			renderer->add(1, index, cells[index].get());
		}
	}

	if (false == initialize_blocks())
	{
		return false;
	}
	
	current_block = make_block(get_start_point());
	renderer->add(2, 0, current_block.get());

	updater->add(0, this);
	return true;
}

// https://imgur.com/a/GZae9T8
bool CppTetris::Tetris::initialize_blocks() noexcept
{
	// I-block 
	// бс(бс)бсбс
	//
	dic_block_rot['I'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(2, 0)}
			, std::vector<Point>{P(0, 0), P(0, 1), P(0, 2), P(0, 3)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(2, 0)}
			, std::vector<Point>{P(0, 0), P(0, 1), P(0, 2), P(0, 3)}
		}
	);
	blocks['I'] = std::make_unique<BlockObject>(dic_block_rot['I'].get(), Color::cyan);

	// J-block 
	// бс(бс)бс
	//      бс
	dic_block_rot['J'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(1, -1)}
		}
	);
	blocks['J'] = std::make_unique<BlockObject>(dic_block_rot['J'].get(), Color::blue);

	// L-block 
	// бс(бс)бс
	// бс
	dic_block_rot['L'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(-1, 1), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -1), P(-1, -1), P(0, 0), P(0, 1)}
			, std::vector<Point>{P(1, 0), P(1, -1), P(0, 0), P(-1, 0)}
			, std::vector<Point>{P(0, 1), P(1, 1), P(0, 0), P(0, -1)}
		}
	);
	blocks['L'] = std::make_unique<BlockObject>(dic_block_rot['L'].get(), Color::dark_green);

	// O-block 
	// бс(бс)
	// бс бс
	dic_block_rot['O'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
		}
	);
	blocks['O'] = std::make_unique<BlockObject>(dic_block_rot['O'].get(), Color::yellow);

	// S-block 
	//   (бс)бс
	// бс бс
	dic_block_rot['S'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, -1), P(1, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(1, 0), P(1, 1)}
		}
	);
	blocks['S'] = std::make_unique<BlockObject>(dic_block_rot['S'].get(), Color::green);


	// T-block 
	// бс(бс)бс
	//    бс
	dic_block_rot['T'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(0, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, -1), P(-1, 0)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(0, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, 1), P(1, 0)}
		}
	);
	blocks['T'] = std::make_unique<BlockObject>(dic_block_rot['T'].get(), Color::dark_margenta);

	// Z-block 
	// бс(бс)
	//    бсбс
	dic_block_rot['Z'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(-1, 0), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(0, -1), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(1, 0), P(1, -1)}
		}
	);
	blocks['Z'] = std::make_unique<BlockObject>(dic_block_rot['Z'].get(), Color::dark_red);

	return true;
}

std::unique_ptr<BlockObject> Tetris::make_block(const Point& center) noexcept
{
	auto iter = blocks.begin();
	std::advance(iter, rand_between(0, blocks.size()));

	auto prototype_block = iter->second.get();
	return std::make_unique<BlockObject>(center, prototype_block);
}

void Tetris::update(float delta) noexcept
{
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

Point CppTetris::Tetris::get_start_point() noexcept
{
	return P((GAME_WIDTH / 2), 0);
}

TETRIS_END
