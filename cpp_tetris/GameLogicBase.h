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

	void render(Renderer* const renderer) noexcept;
	void update(Updater* const updater, float delta) noexcept;

	bool start_game();
	virtual bool initialize() noexcept abstract;

	void set_game(Game* game) { m_game = game; }
	Game* get_game() const { return m_game; }

private:
	Game* m_game;
};

