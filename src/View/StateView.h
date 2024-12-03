#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Observer/IObserver.h"

class StateView : public IObserver
{
public:
	virtual void render() = 0;
	virtual ~StateView() = default;
	virtual void registerSelf() = 0;
};