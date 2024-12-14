#pragma once

#include <string>
#include "Event.h"

class BackEvent : public Event
{
public:
	BackEvent() : Event("Back Event") {}
};