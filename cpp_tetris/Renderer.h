#pragma once
#include <map>
#include <memory>
#include "DoubleBufferedConsole.h"

struct IRenderable;
class Renderer 
{
public:
	typedef DoubleBufferedConsole<wchar_t> DoubleBuffering;
	typedef int order;

	explicit Renderer(LPCWSTR title, const short width, const short height);
	virtual ~Renderer();
	
	void render() const noexcept;
	void add(int order, IRenderable* object) noexcept;

	void write(const int x, const int y, const wchar_t c, unsigned short attribute);

private:
	std::map<int, IRenderable*> objects;
	std::unique_ptr<DoubleBuffering> buffer;
};
