#pragma once

#include "StateController.h"
#include "../Model/LogInModel.h"

class LogInController : public StateController, public std::enable_shared_from_this<LogInController>
{
public:
	LogInController();
	LogInController(std::shared_ptr<LogInModel> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
	void updateGameState();
private:
	std::shared_ptr<LogInModel> model;
	bool isIconClicked(Texture2D icon, Vector2 position, float scale);
	void updateKeyboard();
	void updateMouse();
};