#include "BlockObject.h"

TETRIS_START

BlockObject::BlockObject(Point center, BlockWithRotations* cached)
	: center(center)
	, points(cached)
	, current_rotate(0)
{

}

BlockObject::~BlockObject()
{

}

void BlockObject::rotate() noexcept
{
	current_rotate = (++current_rotate) % Constant::COUNT_ROTATION;
}

const std::vector<Point>& BlockObject::get_points() const
{
	return points->at(current_rotate);
}

TETRIS_END