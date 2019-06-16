#pragma once
#include "Define.h"
#include "IRenderable.h"

TETRIS_START

class Cell;
class BlockObject
{
public:
	explicit BlockObject(Point center, BlockWithRotations* cached);
	virtual ~BlockObject();

	void rotate() noexcept;

	const std::vector<Point>& get_points() const;

public:

private:
	BlockWithRotations* points;

	Point center;
	int current_rotate;
};

TETRIS_END