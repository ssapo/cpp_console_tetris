#include "BlockObject.h"
#include "Renderer.h"

TETRIS_START

BlockObject::BlockObject(int block_index, BlockWithRotations* rotation_infos, int rotate_value, const Point& new_center, unsigned short color_value, bool is_ready)
	: index(block_index)
	, points(rotation_infos)
	, current_rotate(rotate_value)
	, center(new_center)
	, color(color_value)
	, ready(is_ready)
{

}

BlockObject::BlockObject(int index, BlockWithRotations* cached, unsigned short c)
	: BlockObject(index, cached, 0, P(0, 0), c, false)
{

}

BlockObject::BlockObject(BlockWithRotations* cached, unsigned short c)
	: BlockObject(0, cached, c)
{

}

BlockObject::BlockObject(int index, const Point& p, const BlockObject* prototype_block)
	: BlockObject(index, p, *prototype_block)
{

}

BlockObject::BlockObject(int index, const Point& p, const BlockObject& prototype_block)
	: BlockObject(index, prototype_block.points, 0, p, prototype_block.color, false)
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

void BlockObject::to_ready() noexcept
{
	ready = true;
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
