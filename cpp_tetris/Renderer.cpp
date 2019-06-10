#include "Renderer.h"
#include "IRenderable.h"

Renderer::Renderer(LPCWSTR title, const short width, const short height)
	: buffer(std::make_unique<DoubleBuffering>(title, width, height))
{

}

Renderer::~Renderer()
{

}

void Renderer::render() const noexcept
{
	for (const auto& e : objects)
	{
		e.second->render();
	}
}

void Renderer::add(int order, IRenderable* object) noexcept
{
	objects.emplace(order, object);
}

