#pragma once
#include "GameLogicBase.h"

class Board;
class Game;
class Tetris : public GameLogicBase
{
public:
	explicit Tetris();
	virtual ~Tetris();

	virtual bool initialize() override;

private:
	std::unique_ptr<Board> board;

};
