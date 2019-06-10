#pragma once
#include <map>
#include <memory>
#include "DoubleBufferedConsole.h"

struct IRenderable;
class Renderer : std::enable_shared_from_this<Renderer>
{
public:
	typedef DoubleBufferedConsole<wchar_t> DoubleBuffering;
	typedef int order;

	explicit Renderer(LPCWSTR title, const short width, const short height);
	virtual ~Renderer();

	void render() const noexcept;

	void add(int order, IRenderable* object) noexcept;

private:
	std::map<int, IRenderable*> objects;
	std::unique_ptr<DoubleBuffering> buffer;
};
