#pragma once
#include "GameLogicBase.h"
#include "IUpdatable.h"
#include <array>

class Board;
class Game;
class Cell;
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

private:
	std::unique_ptr<Board> board;
	std::array<std::unique_ptr<Cell>, TOTAL_CELLS> cells;
};
