#pragma once

#include <raylib.h>
#include "StateView.h"
#include "../Model/SettingModel.h"
#include "../SoundManager/SoundManager.h"

class SettingView : public StateView, public std::enable_shared_from_this<StateView>
{
private:
	std::shared_ptr<SettingModel> model;
public:
	SettingView(std::shared_ptr<SettingModel> settingModel);
	~SettingView() = default;

	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
};