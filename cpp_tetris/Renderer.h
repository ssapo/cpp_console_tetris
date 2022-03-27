#pragma once
#include <map>
#include <memory>
#include "DoubleBufferedConsole.h"
#include <consoleapi2.h>

struct IRenderable;
class Renderer 
{
public:
	typedef DoubleBufferedConsole<wchar_t> DoubleBuffering;
	typedef int order;

	explicit Renderer(LPCWSTR title);
	virtual ~Renderer();
	
	void render() noexcept;
	void add(int order, int sort, IRenderable& object) noexcept;

	void write(const int x, const int y, const wchar_t c, unsigned short attribute);

public:
	// All the foreground colors except DarkCyan, the background color:
	struct TextColor
	{
		static constexpr unsigned short black			= NULL;
		static constexpr unsigned short dark_blue		= FOREGROUND_BLUE;
		static constexpr unsigned short dark_green		= FOREGROUND_GREEN;
		static constexpr unsigned short dark_cyan		= dark_green | dark_blue;
		static constexpr unsigned short dark_red		= FOREGROUND_RED;
		static constexpr unsigned short dark_margenta	= dark_red | dark_blue;
		static constexpr unsigned short dark_yellow		= dark_red | dark_green;
		static constexpr unsigned short dark_gray		= dark_red | dark_green | dark_blue;
		static constexpr unsigned short light			= FOREGROUND_INTENSITY;
		static constexpr unsigned short gray			= light;
		static constexpr unsigned short blue			= light | dark_blue;
		static constexpr unsigned short green			= light | dark_green;
		static constexpr unsigned short cyan			= light | dark_cyan;
		static constexpr unsigned short red				= light | dark_red;
		static constexpr unsigned short margenta		= light | dark_margenta;
		static constexpr unsigned short yellow			= light | dark_yellow;
		static constexpr unsigned short white			= light | dark_gray;
	};

	struct TextCell
	{
		static constexpr wchar_t fill = L'¡á';
		static constexpr wchar_t empty = L' ';
		static constexpr wchar_t dot = L'¡¤';
	};

private:
	std::map<int, std::unique_ptr<std::map<int, IRenderable*>>> objects;
	std::unique_ptr<DoubleBuffering> buffer;
};
