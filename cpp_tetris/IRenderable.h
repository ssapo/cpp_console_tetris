#pragma once
class Renderer;
struct IRenderable
{
	virtual void render(Renderer* const renderer) noexcept abstract;
};

