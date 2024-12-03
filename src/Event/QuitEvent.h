#pragma once

#include "../Event/Event.h"
#include <string>

class QuitEvent : public Event
{
public:
	QuitEvent() : Event("Quit Event") {}
};