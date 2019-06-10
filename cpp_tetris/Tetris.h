#pragma once
#include "GameLogicBase.h"

class Board;
class Tetris : public GameLogicBase
{
public:
	explicit Tetris();
	virtual ~Tetris();

private:

	std::unique_ptr<Board> board;
};
