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

private:
	bool initialize_blocks() noexcept;
	
	void update_sec(float sec) noexcept;
	
	BlockObject* make_block_random() noexcept;
	BlockObject* make_block_key(const char c) noexcept;
	BlockObject* make_block(const BlockObject* const block) noexcept;
	
	Point get_start_point(const BlockObject* const object) const noexcept;

	void set_block_to_cells(BlockObject* block) noexcept;
	void set_block_to_cells(const Point& p, unsigned short c) noexcept;
	void set_blocks_to_cells() noexcept;

	void cleanup_cells() noexcept;
	bool interaction_cells(const std::vector<Point>& points) const noexcept;
	void move_down() noexcept;

public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr int CELL_WIDTH = (GAME_WIDTH - 2);
	static constexpr int CELL_HEIGHT = (GAME_HEIGHT - 2);
	static constexpr int TOTAL_CELLS = (CELL_WIDTH) * (CELL_HEIGHT);

	static constexpr float TIME_SEC = 1.0f;

private:
	std::unique_ptr<Board> board;
	std::array<std::unique_ptr<Cell>, TOTAL_CELLS> cells;
	std::unordered_map<char, std::unique_ptr<BlockObject>> prototypes;
	std::unordered_map<char, std::unique_ptr<BlockWithRotations>> dic_block_rot;
	
	std::unordered_map<int, std::unique_ptr<BlockObject>> blocks;
	BlockObject* current_block;
	int block_index;

	float sec_timer;
	float frame_timer;
};

TETRIS_END