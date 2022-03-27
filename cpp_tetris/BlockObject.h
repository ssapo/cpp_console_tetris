#pragma once
#include "Define.h"
#include "IRenderable.h"
#include "Point.h"

TETRIS_START

class Cell;

class BlockObject : public IRenderable
{
public:
	explicit BlockObject(int block_index
		, BlockWithRotations* rotation_infos
		, int rotate_value
		, const Point& new_center
		, unsigned short color_value
		, bool is_ready);

	explicit BlockObject(int index, BlockWithRotations* cached, unsigned short c);
	explicit BlockObject(BlockWithRotations* cached, unsigned short c);
	explicit BlockObject(int index, const Point& center, const BlockObject& prototype_block);

	virtual ~BlockObject();

	void next_rotate() noexcept;
	void prev_rotate() noexcept;

	Point get_center() const noexcept { return center; }
	void set_center(const Point& p) noexcept { center = p; }
	void move_center(const Point& p) noexcept { center = point_add(center, p); }

	std::vector<Point> get_points() const { return points->at(current_rotate); }
	std::vector<Point> get_points_added_center(const Point& p) const;
	std::vector<Point> get_points_added_center() const;

	const BlockWithRotations* get_rotations() const { return points; }
	const unsigned short get_color() const { return color; }

	int get_index() const noexcept { return index; }
	void set_index(int new_index) noexcept { index = new_index; }

	bool is_ready() const noexcept { return ready; }
	void to_ready() noexcept;

	virtual void render(Renderer* const renderer) noexcept override;

private:
	BlockWithRotations* points;

	Point center;
	int current_rotate;
	int index;
	unsigned short color;

	bool ready;
};

TETRIS_END