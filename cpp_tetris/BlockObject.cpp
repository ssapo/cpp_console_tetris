#include "BlockObject.h"
#include "Renderer.h"

TETRIS_START

BlockObject::BlockObject(BlockWithRotations* cached, unsigned short c)
	: center(center)
	, points(cached)
	, current_rotate(0)
	, color(c)
{

}

BlockObject::BlockObject(const Point& center, const BlockObject* prototype_block)
	: BlockObject(center, *prototype_block)
{

}

BlockObject::BlockObject(const Point& center, const BlockObject& prototype_block)
	: center(prototype_block.calculate_center(center))
	, points(prototype_block.points)
	, current_rotate(0)
	, color(prototype_block.color)
{

}

BlockObject::~BlockObject()
{

}

Point BlockObject::calculate_center(const Point& center) const noexcept
{
	return P(get_x(center) - get_width(get_points()) / 2, get_y(center));
}

std::vector<Point> BlockObject::get_points_added_center() const
{
	auto retVal = std::vector<Point>();
	auto p = get_points();
	for (const auto& e : p)
	{
		retVal.push_back(point_add(center, e));
	}

	return retVal;
}

void BlockObject::rotate() noexcept
{
	current_rotate = (++current_rotate) % Constant::COUNT_ROTATION;
}

void BlockObject::move(const Point& p) noexcept
{
	center = point_add(center, p);
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
