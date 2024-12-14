#pragma once

#include "StateController.h"
#include "../Model/Pause.h"
#include "../Event/EventManager.h"
#include "../Event/StateChangeEvent.h"
#include "../Event/BackEvent.h"
#include "../Model/GameData.h"

class PauseController : public StateController, public std::enable_shared_from_this<PauseController>
{
public:
	PauseController();
	PauseController(std::shared_ptr<Pause> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
private:
	std::shared_ptr<Pause> model;
};