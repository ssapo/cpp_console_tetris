#pragma once
#include "Define.h"

#define P(X, Y) (Point((X), (Y)))

TETRIS_START

typedef std::tuple<int, int> Point;
typedef std::array<std::vector<Point>, Constant::COUNT_ROTATION> BlockWithRotations;

int getX(const Point& p);
int getY(const Point& p);
Point point_add(const Point& a, const Point& b);
int get_width(const std::vector<Point>& rotations);
int get_width(const std::vector<Point>* rotations);

TETRIS_END