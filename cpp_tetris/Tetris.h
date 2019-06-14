#pragma once
#include "GameLogicBase.h"
#include "Cell.h"
#include "IUpdatable.h"

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

private:
	std::unique_ptr<Board> board;
	std::array<std::unique_ptr<Cell>, (GAME_WIDTH * GAME_HEIGHT)> cells;
};
