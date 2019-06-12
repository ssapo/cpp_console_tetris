#pragma once
#include <map>
#include <memory>

struct IUpdatable;
class Updater
{
public:
	typedef int order;

	explicit Updater();
	virtual ~Updater();

	void update(const float& delta) noexcept;

	void add(int order, IUpdatable* object) noexcept;

private:
	std::map<order, IUpdatable*> objects;
};
