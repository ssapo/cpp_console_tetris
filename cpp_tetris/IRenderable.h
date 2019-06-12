#pragma once
class Renderer;
struct IRenderable
{
	virtual void render(const Renderer* renderer) noexcept abstract;
};

