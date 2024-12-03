#pragma once

#include "../Event/Event.h"
#include <string>

class TickEvent : public Event
{
public:
	TickEvent() : Event("Tick Event") {}
};