#pragma once
#include "Define.h"
#include "GameLogicBase.h"
#include "IUpdatable.h"

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

	virtual bool initialize() override;

	virtual void update(float delta) noexcept override;

public:
	static constexpr int GAME_WIDTH = 15;
	static constexpr int GAME_HEIGHT = 25;
	static constexpr int CELL_WIDTH = (GAME_WIDTH - 2);
	static constexpr int CELL_HEIGHT = (GAME_HEIGHT - 2);
	static constexpr int TOTAL_CELLS = (CELL_WIDTH) * (CELL_HEIGHT);

	static constexpr float TIME_SEC = 1.0f;

private:
	std::unique_ptr<Board> board;
	std::array<std::unique_ptr<Cell>, TOTAL_CELLS> cells;
	std::vector<std::unique_ptr<BlockObject>> blocks;

	float sec_timer;
	float frame_timer;
};

TETRIS_END