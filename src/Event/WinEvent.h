#pragma once

#include "Event.h"

class WinEvent : public Event
{
public:
	WinEvent() : Event("Win Event") {}
};