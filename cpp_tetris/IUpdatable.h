#pragma once
struct IUpdatable
{
	virtual void update(float delta) noexcept abstract;
};
