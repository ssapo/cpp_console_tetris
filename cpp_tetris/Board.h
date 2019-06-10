#pragma once
#include "IRenderable.h"
#include "IUpdatable.h"

class Board : public IRenderable, public IUpdatable
{
public:
	explicit Board();
	virtual ~Board();


private:

};

