#pragma once
#include <tuple>
#include <vector>
#include <array>
#include <memory>

#define TETRIS_START namespace CppTetris {
#define TETRIS_END };
#define USING_TETRIS using namespace CppTetris;

TETRIS_START

struct Constant
{
	static constexpr int COUNT_ROTATION = 4;
};

typedef std::tuple<int, int> Point;
typedef std::array<std::vector<Point>, Constant::COUNT_ROTATION> BlockWithRotations;

TETRIS_END