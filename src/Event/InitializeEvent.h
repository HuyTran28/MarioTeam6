#pragma once

#include "../Event/Event.h"
#include <string>

class InitializeEvent : public Event
{
public:
	InitializeEvent() : Event("Initialize Event") {}
};