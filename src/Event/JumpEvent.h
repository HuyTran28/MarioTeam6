#pragma once

#include <raylib.h>
#include "Event.h"

class JumpEvent : public Event
{
public:
	JumpEvent() : Event("Jump Event") {}
};