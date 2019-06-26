#pragma once
#include "Define.h"
#include "IRenderable.h"
#include "Point.h"

TETRIS_START

class Cell;
class BlockObject : public IRenderable
{
public:
	explicit BlockObject(BlockWithRotations* cached, unsigned short c);
	explicit BlockObject(const Point& center, const BlockObject* prototype_block);
	explicit BlockObject(const Point& center, const BlockObject& prototype_block);
	virtual ~BlockObject();

	void rotate() noexcept;

	Point calculate_center(const Point& point) const noexcept;
	const std::vector<Point>& get_points() const { return points->at(current_rotate); }
	const BlockWithRotations* get_rotations() const { return points; }
	virtual void render(Renderer* const renderer) noexcept override;

private:
	BlockWithRotations* points;

	Point center;
	int current_rotate;
	unsigned short color;
};

TETRIS_END