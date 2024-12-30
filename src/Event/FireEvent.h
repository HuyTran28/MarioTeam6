#pragma once

#include "Event.h"

class FireEvent : public Event
{
public:
	FireEvent() : Event("Fire Event") {}
};