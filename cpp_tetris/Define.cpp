#include "Define.h"

int CppTetris::rand_between(int min, int max) noexcept
{
	static std::random_device rn;
	static std::mt19937_64 rnd(rn());

	std::uniform_int_distribution<int> range(min, max - 1);
	return range(rnd);
}
