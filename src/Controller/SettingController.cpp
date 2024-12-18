#include "SettingController.h"

SettingController::SettingController(std::shared_ptr<SettingModel> settingModel)
{
	model = settingModel;
}

void SettingController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		if (model->getBackButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<BackEvent>());
			return;
		}
		if (model->getVolumeUpButton()->isClicked(GetMousePosition()))
		{
			SoundManager::getInstance()->SetVolume(SoundManager::getInstance()->GetVolume() + 0.1f);
			return;
		}
		if (model->getVolumeDownButton()->isClicked(GetMousePosition()))
		{
			SoundManager::getInstance()->SetVolume(SoundManager::getInstance()->GetVolume() - 0.1f);
			return;
		}
		if (model->getVolumeMuteButton()->isClicked(GetMousePosition()))
		{
			SoundManager::getInstance()->SetVolume(0.0f);
			return;
		}
		if (model->getVolumeUnmuteButton()->isClicked(GetMousePosition()))
		{
			SoundManager::getInstance()->SetVolume(1.0f);
			return;
		}
	}
}

void SettingController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

