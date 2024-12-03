#pragma once

#include "../Event/Event.h"
#include <memory>

class IObserver
{
public:
	virtual void update(std::shared_ptr<Event>) = 0;
	virtual ~IObserver() = default;
};