#include "Renderer.h"
#include "IRenderable.h"

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
		e.second->render(this);
	}

	buffer->flip();
}

void Renderer::add(int order, IRenderable* object) noexcept
{
	objects.emplace(order, object);
}

void Renderer::write(const int x, const int y, const wchar_t c, unsigned short attribute)
{
	buffer->write(x, y, c, attribute);
}

