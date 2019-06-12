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
	buffer->clear(L' ', BACKGROUND_INTENSITY);

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

