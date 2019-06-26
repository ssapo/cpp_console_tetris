#pragma once
#include <tuple>
#include <vector>
#include <array>
#include <memory>
#include <random>
#include "Renderer.h"

#define TETRIS_START namespace CppTetris {
#define TETRIS_END };
#define USING_TETRIS using namespace CppTetris;

TETRIS_START

struct Constant
{
	static constexpr int COUNT_ROTATION = 4;
};

typedef Renderer::TextColor Color;
int rand_between(int min, int max) noexcept;
TETRIS_END