#include "SettingView.h"
#include <iostream>

SettingView::SettingView(std::shared_ptr<SettingModel> settingModel) : model(settingModel) {}

void SettingView::render() {
	ClearBackground(RAYWHITE);
	BeginDrawing();

	DrawText(model->getSettingText().c_str(), GetScreenWidth() / 2.0f - (1200.0f - 770.0f) / 2.0f, 150.0f, 120, BLACK);
	std::string volumeText = std::to_string((int)(SoundManager::getInstance()->GetVolume() * 100.0f));
	DrawText(volumeText.c_str(), GetScreenWidth() / 2.0f - (1060.0f - 950.0f) / 2.0f, GetScreenHeight() / 2.0f, 100, BLACK);

	std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

	model->getBackButton()->draw();
	model->getVolumeUpButton()->draw();
	model->getVolumeDownButton()->draw();
	model->getVolumeMuteButton()->draw();
	model->getVolumeUnmuteButton()->draw();

	EndDrawing();
}

void SettingView::update(std::shared_ptr<Event> event) {
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void SettingView::registerSelf() {
	EventManager::getInstance().addObserver(shared_from_this());
}
