#include "SettingModel.h"

SettingModel::SettingModel()
{


	Texture2D backTexture = LoadTexture("..\\..\\Assets\\Icons\\back-arrow.png");
	Rectangle srcRecBack = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
	Rectangle dstRecBack = { 50.0f, 50.0f, buttonSize, buttonSize };

	backButton = std::make_shared<Button>("Back To Menu", backTexture, srcRecBack, dstRecBack, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D muteTexture = LoadTexture("..\\..\\Assets\\Icons\\mute.png");
	Rectangle srcRecMute = { 0.0f, 0.0f, (float)muteTexture.width, (float)muteTexture.height };
	Rectangle dstRecMute = { 250.0f, GetScreenHeight() / 2.0f, buttonSize, buttonSize };

	volumeMuteButton = std::make_shared<Button>("", muteTexture, srcRecMute, dstRecMute, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D minus = LoadTexture("..\\..\\Assets\\Icons\\minus.png");
	Rectangle srcRecMinus = { 0.0f, 0.0f, (float)minus.width, (float)minus.height };
	Rectangle dstRecMinus = { 650.0f, GetScreenHeight() / 2.0f, buttonSize, buttonSize };

	volumeDownButton = std::make_shared<Button>("", minus, srcRecMinus, dstRecMinus, Vector2{0.0f, 0.0f}, 0.0f, WHITE);

	Texture2D plus = LoadTexture("..\\..\\Assets\\Icons\\plus.png");
	Rectangle srcRecPlus = { 0.0f, 0.0f, (float)plus.width, (float)plus.height };
	Rectangle dstRecPlus = { GetScreenWidth() - 650.0f - buttonSize, GetScreenHeight() / 2.0f - 20.0f, buttonSize + 40.0f, buttonSize + 40.0f };

	volumeUpButton = std::make_shared<Button>("", plus, srcRecPlus, dstRecPlus, Vector2{0.0f, 0.0f}, 0.0f, WHITE);

	Texture2D unmute = LoadTexture("..\\..\\Assets\\Icons\\volume.png");
	Rectangle srcRecUnmute = { 0.0f, 0.0f, (float)unmute.width, (float)unmute.height };
	Rectangle dstRecUnmute = { GetScreenWidth() - 250.0f - buttonSize, GetScreenHeight() / 2.0f - 10.0f, buttonSize + 20.0f, buttonSize + 20.0f };

	volumeUnmuteButton = std::make_shared<Button>("", unmute, srcRecUnmute, dstRecUnmute, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	settingText = "Setting";
}

std::shared_ptr<Button> SettingModel::getBackButton() const
{
	return backButton;
}

std::shared_ptr<Button> SettingModel::getVolumeUpButton() const
{
	return volumeUpButton;
}

std::shared_ptr<Button> SettingModel::getVolumeDownButton() const
{
	return volumeDownButton;
}

std::shared_ptr<Button> SettingModel::getVolumeMuteButton() const
{
	return volumeMuteButton;
}

std::shared_ptr<Button> SettingModel::getVolumeUnmuteButton() const
{
	return volumeUnmuteButton;
}

std::string SettingModel::getSettingText() const
{
	return settingText;
}

