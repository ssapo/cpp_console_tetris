#include "Point.h"

TETRIS_START

int getX(const Point& p)
{
	return std::get<0>(p);
}

int getY(const Point& p)
{
	return std::get<1>(p);
}

Point point_add(const Point& a, const Point& b)
{
	return P(getX(a) + getX(b), getY(a) + getY(b));
}

int get_width(const std::vector<Point>* rotations)
{
	return get_width(*rotations);
}

int get_width(const std::vector<Point>& rotations)
{
	static auto pr = [](const Point& p1, const Point& p2)
	{
		return getX(p1) < getX(p2);
	};

	auto minx = *std::min_element(rotations.begin(), rotations.end(), pr);
	auto maxx = *std::max_element(rotations.begin(), rotations.end(), pr);
	return getX(maxx) - getX(minx);
}

TETRIS_END