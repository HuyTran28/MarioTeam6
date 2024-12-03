#pragma once

#include <raylib.h>
#include "../Event/Event.h"
#include "../Event/EventManager.h"
#include "../Observer/IObserver.h"
#include "../Event/KeyboardEvent.h"
#include "../Event/MouseClickedEvent.h"

class InputHandler : public IObserver, public std::enable_shared_from_this<InputHandler>
{
public:
	InputHandler();
	void update(std::shared_ptr<Event> event) override;
	void registerSelf();
};