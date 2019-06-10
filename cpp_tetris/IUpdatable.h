#pragma once
struct IUpdatable
{
	virtual void update(const float& delta) noexcept abstract;
};
