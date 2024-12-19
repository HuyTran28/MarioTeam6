#pragma once

#include "StateController.h"
#include "../Model/GameOverModel.h"
#include "../Event/StateChangeEvent.h"

class GameOverController : public StateController, public std::enable_shared_from_this<GameOverController>
{
public:
	GameOverController(std::shared_ptr<GameOverModel> gameOverModel);
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
private:
	std::shared_ptr<GameOverModel> model;
};