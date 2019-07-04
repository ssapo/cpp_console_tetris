#include "BlockObject.h"
#include "Renderer.h"

TETRIS_START

BlockObject::BlockObject(int index, BlockWithRotations* cached, unsigned short c)
	: center(center)
	, index(index)
	, points(cached)
	, current_rotate(0)
	, color(c)
{

}

BlockObject::BlockObject(BlockWithRotations* cached, unsigned short c)
	: BlockObject(0, cached, c)
{

}

BlockObject::BlockObject(int index, const Point& center, const BlockObject* prototype_block)
	: BlockObject(index, center, *prototype_block)
{

}

BlockObject::BlockObject(int index, const Point& c, const BlockObject& prototype_block)
	: center(c)
	, index(index)
	, points(prototype_block.points)
	, current_rotate(0)
	, color(prototype_block.color)
{

}

BlockObject::~BlockObject()
{

}

std::vector<Point> BlockObject::get_points_added_center(const Point& c) const
{
	auto retVal = std::vector<Point>();
	auto p = get_points();
	for (const auto& e : p)
	{
		retVal.push_back(point_add(point_add(center, c), e));
	}

	return retVal;
}

std::vector<Point> BlockObject::get_points_added_center() const
{
	return get_points_added_center(P(0, 0));
}

void BlockObject::rotate() noexcept
{
	current_rotate = (++current_rotate) % Constant::COUNT_ROTATION;
}

void BlockObject::render(Renderer* const renderer) noexcept
{
	auto p = points->at(current_rotate);
	for (auto& e : p)
	{
		auto rp = point_add(center, e);
		renderer->write(get_x(rp) + 1, get_y(rp) + 1, L'бс', color);
	}
}

TETRIS_END
