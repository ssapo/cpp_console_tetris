#include "Renderer.h"
#include "IRenderable.h"
#include <memory>

Renderer::Renderer(LPCWSTR title)
	: buffer(std::make_unique<DoubleBuffering>(title, 100, 100))
{

}

Renderer::~Renderer()
{

}

void Renderer::render() noexcept
{
	buffer->clear(L' ', NULL);

	for (const auto& e : objects)
	{
		if (nullptr == e.second)
		{
			continue;
		}

		const auto& container = *(e.second);
		for (const auto& f : container)
		{
			f.second->render(this);
		}
	}

	buffer->flip();
}

void Renderer::add(int order, int sort, IRenderable& object) noexcept
{
	if (objects.end() == objects.find(order))
	{
		auto map = std::make_unique<std::map<int, IRenderable*>>();
		map->emplace(sort, &object);
		objects.emplace(order, std::move(map));
	}
	else
	{
		auto map = objects[order].get();
		map->emplace(std::make_pair(sort, &object));
	}
}

void Renderer::write(const int x, const int y, const wchar_t c, unsigned short attribute)
{
	buffer->write(x * 2, y, c, attribute);
	buffer->write(x * 2 + 1, y, TextCell::empty, attribute);
}

