#pragma once

#include "Event.h"

class DieEvent : public Event
{
public:
	DieEvent() : Event("Die Event") {}
};