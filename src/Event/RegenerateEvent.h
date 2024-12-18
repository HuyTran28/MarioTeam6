#pragma once

#include <raylib.h>
#include "Event.h"

class RegenerateEvent : public Event
{
public:
	RegenerateEvent() : Event("Regenerate Event") {}
};