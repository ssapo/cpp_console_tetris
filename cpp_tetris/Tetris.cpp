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
	, block_index(0)
	, current_block(nullptr)
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

	updater->add(0, this);
	return true;
}

// https://imgur.com/a/GZae9T8
bool CppTetris::Tetris::initialize_blocks() noexcept
{
	// I-block 
	// ■(■)■■
	//
	dic_block_rot['I'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -2), P(0, 1), P(0, 0), P(0, -1)}
			, std::vector<Point>{P(2, 0), P(-1, 0), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -2), P(0, 1), P(0, 0), P(0, -1)}
		}
	);
	prototypes['I'] = std::make_unique<BlockObject>(dic_block_rot['I'].get(), Color::cyan);

	// J-block 
	// ■(■)■
	//      ■
	dic_block_rot['J'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, -1), P(1, -1)}
		}
	);
	prototypes['J'] = std::make_unique<BlockObject>(dic_block_rot['J'].get(), Color::blue);

	// L-block 
	// ■(■)■
	// ■
	dic_block_rot['L'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(-1, 1), P(0, 0), P(1, 0)}
			, std::vector<Point>{P(0, -1), P(-1, -1), P(0, 0), P(0, 1)}
			, std::vector<Point>{P(1, 0), P(1, -1), P(0, 0), P(-1, 0)}
			, std::vector<Point>{P(0, 1), P(1, 1), P(0, 0), P(0, -1)}
		}
	);
	prototypes['L'] = std::make_unique<BlockObject>(dic_block_rot['L'].get(), Color::white);

	// O-block 
	// ■(■)
	// ■ ■
	dic_block_rot['O'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(-1, 1)}
		}
	);
	prototypes['O'] = std::make_unique<BlockObject>(dic_block_rot['O'].get(), Color::yellow);

	// S-block 
	//   (■)■
	// ■ ■
	dic_block_rot['S'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(1, 0), P(0, 0), P(0, 1), P(-1, 1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(-1, 0), P(-1, -1)}
			, std::vector<Point>{P(-1, 0), P(0, 0), P(0, -1), P(1, -1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(1, 0), P(1, 1)}
		}
	);
	prototypes['S'] = std::make_unique<BlockObject>(dic_block_rot['S'].get(), Color::green);


	// T-block 
	// ■(■)■
	//    ■
	dic_block_rot['T'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(1, 0), P(0, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(0, -1), P(-1, 0)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(-1, 0), P(0, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(0, 1), P(1, 0)}
		}
	);
	prototypes['T'] = std::make_unique<BlockObject>(dic_block_rot['T'].get(), Color::margenta);

	// Z-block 
	// ■(■)
	//    ■■
	dic_block_rot['Z'] = std::make_unique<BlockWithRotations>(
		BlockWithRotations{ std::vector<Point>{P(-1, 0), P(0, 0), P(0, 1), P(1, 1)}
			, std::vector<Point>{P(0, -1), P(0, 0), P(-1, 0), P(-1, 1)}
			, std::vector<Point>{P(1, 0), P(0, 0), P(0, -1), P(-1, -1)}
			, std::vector<Point>{P(0, 1), P(0, 0), P(1, 0), P(1, -1)}
		}
	);
	prototypes['Z'] = std::make_unique<BlockObject>(dic_block_rot['Z'].get(), Color::red);

	return true;
}

BlockObject* Tetris::make_block_random() noexcept
{
	auto iter = prototypes.begin();
	std::advance(iter, rand_between(0, prototypes.size()));
	return make_block(iter->second.get());
}

BlockObject* Tetris::make_block_key(const char key) noexcept
{
	auto prototype_block = prototypes[key].get();
	return make_block(prototypes[key].get());
}

BlockObject* Tetris::make_block(const BlockObject* const block) noexcept
{
	using namespace std;

	auto new_block = new BlockObject(block_index, get_start_point(block), block);
	if (new_block)
	{
		blocks.insert(make_pair(block_index, new_block));
		block_index++;
		return new_block;
	}

	return nullptr;
}

Point Tetris::get_start_point(const BlockObject* const object) const noexcept
{
	return P((GAME_WIDTH / 2) - (get_width(object->get_points()) / 2), 0);
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

void Tetris::set_blocks_to_cells() noexcept
{
	for (const auto& e : blocks)
	{
		auto block = e.second.get();
		set_block_to_cells(block);
	}
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
	cleanup_cells();
	
	if (current_block)
	{
		move_down();
	}
	else
	{
		current_block = make_block_random();
		if (nullptr == current_block)
		{
			// 어떻게 채우지?
		}
	}
	set_blocks_to_cells();
}

void Tetris::move_down() noexcept
{
	auto points = current_block->get_points_added_center(P(0, 1));
	if (false == interaction_cells(points))
	{
		current_block->move_center(P(0, 1));
	}
	else
	{
		current_block = nullptr;
	}
}

bool Tetris::interaction_cells(const std::vector<Point>& points) const noexcept
{
	for (const auto& e : points)
	{
		int x = get_x(e);
		if (x < 0 || x >= CELL_WIDTH)
		{
			return true;
		}

		int y = get_y(e);
		if (y < 0 || y >= CELL_HEIGHT)
		{
			return true;
		}

		auto cell = cells[y * CELL_WIDTH + x].get();
		if (cell->is_fill())
		{
			return true;
		}
	}

	return false;
}

void Tetris::cleanup_cells() noexcept
{
	for (const auto& e : cells)
	{
		e->cleanup();
	}
}

TETRIS_END


