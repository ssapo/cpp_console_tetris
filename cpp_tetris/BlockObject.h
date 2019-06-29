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
	void move(const Point& p) noexcept;

	Point calculate_center(const Point& point) const noexcept;
	std::vector<Point> get_points() const { return points->at(current_rotate); }
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