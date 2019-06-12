#include "Updater.h"
#include "IUpdatable.h"

Updater::Updater()
{

}

Updater::~Updater()
{

}

void Updater::update(const float& delta) noexcept
{
	for (const auto& e : objects)
	{
		e.second->update(delta);
	}
}

void Updater::add(int order, IUpdatable* object) noexcept
{
	objects.emplace(order, object);
}

