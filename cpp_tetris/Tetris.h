#pragma once
#include <unordered_map>
#include "Define.h"
#include "GameLogicBase.h"
#include "IUpdatable.h"
#include "Point.h"

class Game;

TETRIS_START

class Board;
class Cell;
class BlockObject;

class Tetris : public GameLogicBase, public IUpdatable
{
public:
	explicit Tetris();
	virtual ~Tetris();

	virtual bool initialize() noexcept override;
	virtual void update(float delta) noexcept override;
	virtual bool handle_event(char keycode) noexcept override;

private:
	bool initialize_blocks() noexcept;
	
	void update_tick(float sec) noexcept;
	
	std::unique_ptr<BlockObject> make_block_random() noexcept;
	std::unique_ptr<BlockObject> make_block_key(const char c) noexcept;
	std::unique_ptr<BlockObject> make_block(const BlockObject* const block) noexcept;
	
	Point get_start_point(const BlockObject* const object) const noexcept;

	void set_block_to_cells(BlockObject* block) noexcept;
	void set_block_to_cells(const Point& p, unsigned short c) noexcept;
	void set_blocks_to_cells() noexcept;

	void cleanup_cells() noexcept;
	bool intersection_blocks(const std::vector<Point>& points) const noexcept;
	
	bool can_move() const noexcept;
	void rotate() noexcept;
	void move_down() noexcept;
	void move_right() noexcept;
	void move_left() noexcept;
	void move_to_bottom() noexcept;

public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr int CELL_WIDTH = (GAME_WIDTH - 2);
	static constexpr int CELL_HEIGHT = (GAME_HEIGHT - 2);
	static constexpr int TOTAL_CELLS = (CELL_WIDTH) * (CELL_HEIGHT);

	static constexpr float TIME_TICK = 1.0f;

	static constexpr int KEY_LEFT = 75;
	static constexpr int KEY_RIGHT = 77;
	static constexpr int KEY_UP = 72;
	static constexpr int KEY_DOWN = 80;
	static constexpr int KEY_SPACE = 32;
	static constexpr int KEY_EXIT = 27;

private:
	std::unique_ptr<Board> board;
	std::array<std::unique_ptr<Cell>, TOTAL_CELLS> cells;
	std::unordered_map<char, std::unique_ptr<BlockObject>> prototypes;
	std::unordered_map<char, std::unique_ptr<BlockWithRotations>> dic_block_rot;

	std::unordered_map<int, std::unique_ptr<BlockObject>> blocks;
	std::unique_ptr<BlockObject> current_block;
	int block_index;

	float sec_timer;
	float frame_timer;
};

TETRIS_END