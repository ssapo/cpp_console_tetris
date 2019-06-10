#pragma once
#include <memory>

class Game;
class Renderer;
class Updater;
class GameLogicBase
{
public:
	explicit GameLogicBase();
	virtual ~GameLogicBase();

	void render(const Renderer* renderer) noexcept;
	void update(const Updater* updater, const float& delta) noexcept;

private:
};

