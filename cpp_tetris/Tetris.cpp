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

	board = std::make_unique<Board>(width, height, Color::gray);
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
	
	current_block = make_block('J', get_start_point());
	current_block->move(P(0, 19));
	set_block_to_cells(current_block.get());

	current_block = make_block('Z', get_start_point());
	current_block->move(P(0, 16));
	set_block_to_cells(current_block.get());

	current_block = make_block('I', get_start_point());
	current_block->move(P(0, 13));
	set_block_to_cells(current_block.get());

	current_block = make_block('S', get_start_point());
	current_block->move(P(0, 10));
	set_block_to_cells(current_block.get());

	current_block = make_block('O', get_start_point());
	current_block->move(P(0, 7));
	set_block_to_cells(current_block.get());

	current_block = make_block('L', get_start_point());
	current_block->move(P(0, 4));
	set_block_to_cells(current_block.get());

	current_block = make_block('T', get_start_point());
	current_block->move(P(0, 1));
	set_block_to_cells(current_block.get());

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
		BlockWithRotations{ std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -2), P(0, 1), P(0, 0), P(0, -1)}
			, std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -2), P(0, 1), P(0, 0), P(0, -1)}
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
	blocks['L'] = std::make_unique<BlockObject>(dic_block_rot['L'].get(), Color::white);

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
	blocks['T'] = std::make_unique<BlockObject>(dic_block_rot['T'].get(), Color::margenta);

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
	blocks['Z'] = std::make_unique<BlockObject>(dic_block_rot['Z'].get(), Color::red);

	return true;
}

std::unique_ptr<BlockObject> Tetris::make_random_block(const Point& center) noexcept
{
	auto iter = blocks.begin();
	std::advance(iter, rand_between(0, blocks.size()));

	auto prototype_block = iter->second.get();
	auto new_block = std::make_unique<BlockObject>(center, prototype_block);
	return new_block;
}

std::unique_ptr<BlockObject> Tetris::make_block(const char c, const Point& center) noexcept
{
	auto prototype_block = blocks[c].get();
	auto new_block = std::make_unique<BlockObject>(center, prototype_block);
	return new_block;
}

void Tetris::set_block_to_cells(BlockObject* block) noexcept
{
	auto points = block->get_points_added_center();
	for (const auto& e : points)
	{
		set_block_to_cells(e, block->get_color());
	}
}

void Tetris::set_block_to_cells(const Point& p, unsigned short c) noexcept
{
	auto cell = cells[get_y(p) * CELL_WIDTH + get_x(p)].get();
	cell->set_fill_cell();
	cell->set_color(c);
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

TETRIS_END
