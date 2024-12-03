#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Observer/IObserver.h"

class StateController : public IObserver
{
public:
	virtual ~StateController() = default;
	virtual void registerSelf() = 0;
};