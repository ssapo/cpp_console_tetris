#pragma once
#include <tuple>
#include <vector>
#include <array>
#include <memory>
#include <random>


#define TETRIS_START namespace CppTetris {
#define TETRIS_END };
#define USING_TETRIS using namespace CppTetris;
#define P(X, Y) (Point((X), (Y)))

TETRIS_START

struct Constant
{
	static constexpr int COUNT_ROTATION = 4;
};

typedef std::tuple<int, int> Point;
typedef std::array<std::vector<Point>, Constant::COUNT_ROTATION> BlockWithRotations;

int rand_between(int min, int max) noexcept
{
	static std::random_device rn;
	static std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<int> range(min, max - 1);
	return range(rnd);
}
TETRIS_END