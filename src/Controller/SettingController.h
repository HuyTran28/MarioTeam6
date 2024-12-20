#pragma once

#include <raylib.h>
#include "StateController.h"
#include "../Model/SettingModel.h"
#include "../Event/StateChangeEvent.h"
#include "../Event/BackEvent.h"
#include "../SoundManager/SoundManager.h"
#include "../CollisionManager/CollisionManager.h"

class SettingController : public StateController, public std::enable_shared_from_this<StateController>
{
private:
	std::shared_ptr<SettingModel> model;
public:
	SettingController(std::shared_ptr<SettingModel> settingModel);
	~SettingController() = default;

	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
};