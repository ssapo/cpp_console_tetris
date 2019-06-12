#pragma once
#include "GameLogicBase.h"

class Board;
class Tetris : public GameLogicBase
{
public:
	explicit Tetris(const int width, const int height);
	virtual ~Tetris();

private:

	std::unique_ptr<Board> board;
};
