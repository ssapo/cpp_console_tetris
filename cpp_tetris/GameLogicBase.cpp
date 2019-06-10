#include "GameLogicBase.h"
#include "Game.h"
#include "Renderer.h"
#include "Updater.h"

GameLogicBase::GameLogicBase()
{
}

GameLogicBase::~GameLogicBase()
{

}

void GameLogicBase::render(const Renderer* renderer) noexcept
{
	renderer->render();
}

void GameLogicBase::update(const Updater* updater, const float& delta) noexcept
{
	updater->update(delta);
}

