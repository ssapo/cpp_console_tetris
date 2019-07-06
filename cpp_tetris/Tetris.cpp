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

	current_block = make_block_random();

	updater->add(0, this);
	return true;
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
	if (current_block)
	{
		set_block_to_cells(current_block.get());
	}

	for (const auto& e : blocks)
	{
		auto block = e.second.get();
		set_block_to_cells(block);
	}
}

void Tetris::update(float delta) noexcept
{
	cleanup_cells();
	
	frame_timer += delta;
	if (frame_timer >= TIME_TICK)
	{
		frame_timer = 0.0f;
		sec_timer += TIME_TICK;

		update_tick(sec_timer);
	}
	
	set_blocks_to_cells();
}

void Tetris::update_tick(float sec) noexcept
{
	if (can_move())
	{
		move_down();
	}
	else
	{
		current_block->to_ready();
	}
}

void Tetris::move_down() noexcept
{
	auto points = current_block->get_points_added_center(P(0, 1));
	if (false == intersection_blocks(points))
	{
		current_block->move_center(P(0, 1));
	}
	else
	{
		blocks.insert(std::make_pair(block_index, std::move(current_block)));
		block_index++;
		current_block = make_block_random();
	}
}

void Tetris::move_right() noexcept
{
	auto points = current_block->get_points_added_center(P(1, 0));
	if (false == intersection_blocks(points))
	{
		current_block->move_center(P(1, 0));
	}
}

void Tetris::move_left() noexcept
{
	auto points = current_block->get_points_added_center(P(-1, 0));
	if (false == intersection_blocks(points))
	{
		current_block->move_center(P(-1, 0));
	}
}

bool Tetris::can_move() const noexcept
{
	return current_block && current_block->is_ready();
}

void Tetris::rotate() noexcept
{
	current_block->next_rotate();

	auto points = current_block->get_points_added_center();
	if (true == intersection_blocks(points))
	{
		current_block->prev_rotate();
	}
}

void Tetris::move_to_bottom() noexcept
{
	while (can_move())
	{
		move_down();
	}
}

bool Tetris::handle_event(char keycode) noexcept
{
	if (keycode == KEY_LEFT)
	{
		if (can_move())
		{
			move_left();
		}
	}
	else if (keycode == KEY_RIGHT)
	{
		if (can_move())
		{
			move_right();
		}
	}
	else if (keycode == KEY_UP)
	{
		if (can_move())
		{
			rotate();
		}
	}
	else if (keycode == KEY_DOWN)
	{
		if (can_move())
		{
			move_down();
		}
	}
	else if (keycode == KEY_SPACE)
	{
		if (can_move())
		{
			move_to_bottom();
		}
	}
	else if (keycode == KEY_EXIT)
	{
		return false;
	}

	return true;
}

bool Tetris::intersection_blocks(const std::vector<Point>& points) const noexcept
{
	for (const auto& e : points)
	{
		int ex = get_x(e);
		int ey = get_y(e);
		if ((0 > ex || ex >= CELL_WIDTH) ||
			(0 > ey || ey >= CELL_HEIGHT))
		{
			return true;
		}

		for (const auto& f : blocks)
		{
			auto fpoints = f.second->get_points_added_center();
			for (const auto& g : fpoints)
			{
				int gx = get_x(g);
				int gy = get_y(g);

				if (ex == gx && ey == gy)
				{
					return true;
				}
			}
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


