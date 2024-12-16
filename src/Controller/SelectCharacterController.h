#pragma once

#include "StateController.h"
#include "../Model/SelectCharacter.h"
#include "../Event/EventManager.h"
#include "../Event/StateChangeEvent.h"
#include "../Event/BackEvent.h"
#include "../Model/GameData.h"

class SelectCharacterController : public StateController, public std::enable_shared_from_this<SelectCharacterController>
{
public:
	SelectCharacterController();
	SelectCharacterController(std::shared_ptr<SelectCharacter> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
private:
	std::shared_ptr<SelectCharacter> model;
};