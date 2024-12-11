#pragma once

#include <raylib.h>
#include "StateController.h"
#include "../Event/StateChangeEvent.h"
#include "../Model/LevelSelectModel.h"

class LevelSelectController : public StateController, public std::enable_shared_from_this<LevelSelectController>
{
public:
	LevelSelectController();
	LevelSelectController(std::shared_ptr<LevelSelectModel> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
private:
	std::shared_ptr<LevelSelectModel> model;
	//bool isIconClicked(Texture2D icon, Vector2 position, float scale);
	void updateKeyboard();
	void updateMouse();
};