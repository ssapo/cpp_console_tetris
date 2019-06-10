#pragma once
#include <memory>
#include "IRenderable.h"
#include "IUpdatable.h"

class Game;
class GameLogicBase: public IRenderable, public IUpdatable
{
public:
	explicit GameLogicBase(std::shared_ptr<Game> game);
	virtual ~GameLogicBase();

	virtual void render() override;
	virtual void update(const float& delta) override;

private:
	std::weak_ptr<Game> game;
};

