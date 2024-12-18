#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include "StateModel.h"
#include "Button/Button.h"

class SettingModel : public StateModel
{
private:
	std::shared_ptr<Button> backButton;
	std::shared_ptr<Button> volumeUpButton;
	std::shared_ptr<Button> volumeDownButton;
	std::shared_ptr<Button> volumeMuteButton;
	std::shared_ptr<Button> volumeUnmuteButton;
	std::string settingText;
	const int buttonSize = 100;
public:
	SettingModel();
	~SettingModel() = default;

	std::shared_ptr<Button> getBackButton() const;
	std::shared_ptr<Button> getVolumeUpButton() const;
	std::shared_ptr<Button> getVolumeDownButton() const;
	std::shared_ptr<Button> getVolumeMuteButton() const;
	std::shared_ptr<Button> getVolumeUnmuteButton() const;
	std::string getSettingText() const;
};