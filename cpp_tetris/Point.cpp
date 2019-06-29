#include "Point.h"

TETRIS_START

int get_x(const Point& p)
{
	return std::get<0>(p);
}

int get_y(const Point& p)
{
	return std::get<1>(p);
}

Point point_add(const Point& a, const Point& b)
{
	return P(get_x(a) + get_x(b), get_y(a) + get_y(b));
}

int get_width(const std::vector<Point>* points)
{
	return get_width(*points);
}

int get_width(const std::vector<Point>& points)
{
	static auto pr = [](const Point& p1, const Point& p2)
	{
		return get_x(p1) < get_x(p2);
	};

	auto minx = *std::min_element(points.begin(), points.end(), pr);
	auto maxx = *std::max_element(points.begin(), points.end(), pr);
	return get_x(maxx) - get_x(minx) + 1;
}

TETRIS_END