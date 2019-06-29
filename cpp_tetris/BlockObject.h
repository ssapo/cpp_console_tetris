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

	Point get_center() const noexcept { return center; }
	void set_center(const Point& p) noexcept { center = p; }
	void move_center(const Point& p) noexcept { center = point_add(center, p); }
	std::vector<Point> get_points() const { return points->at(current_rotate); }
	std::vector<Point> get_points_added_center(const Point& p) const;
	std::vector<Point> get_points_added_center() const;
	const BlockWithRotations* get_rotations() const { return points; }
	const unsigned short get_color() const { return color; }

	virtual void render(Renderer* const renderer) noexcept override;

private:
	BlockWithRotations* points;

	Point center;
	int current_rotate;
	unsigned short color;
};

TETRIS_END