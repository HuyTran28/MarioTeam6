#pragma once

#include "StateController.h"
#include "../Model/MenuModel.h"
#include "../Event/KeyboardEvent.h"
#include "../Event/MouseClickedEvent.h"
#include <raymath.h>
#include "../Event/StateChangeEvent.h"

class MenuController : public StateController, public std::enable_shared_from_this<MenuController>
{
public:
	MenuController();
	MenuController(std::shared_ptr<MenuModel> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
	void updatePlayerMovement();
	void updateGameState();
	~MenuController();
private:
	std::shared_ptr<MenuModel> model;
};