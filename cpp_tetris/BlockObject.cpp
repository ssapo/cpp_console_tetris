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

CppTetris::BlockObject::BlockObject(const Point& center, const BlockObject* prototype_block)
	: BlockObject(center, *prototype_block)
{

}

CppTetris::BlockObject::BlockObject(const Point& center, const BlockObject& prototype_block)
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
	int width = get_width(get_points());
	return P(getX(center) - ((width / 2)), getY(center));
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
		renderer->write(getX(rp) + 1, getY(rp) + 1, L'бс', color);
	}
}

TETRIS_END
