#pragma once

#include "../Event/Event.h"
#include "IObserver.h"
#include <memory>

class ISubject
{
public:
	virtual void addObserver(std::shared_ptr<IObserver> ob) = 0;
	virtual void removeObserver(std::shared_ptr<IObserver> ob) = 0;
	virtual void notify(std::shared_ptr<Event> event) = 0;
};