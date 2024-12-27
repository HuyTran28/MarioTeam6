#include "WinModel.h"

WinModel::WinModel()
{
	title = "WIN";

	Texture2D backTexture = LoadTexture("..\\..\\Assets\\Icons\\home-button.png");
	Rectangle srcRecBack = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
	Rectangle dstRecBack = { 250.0f, GetScreenHeight() / 2.0f, buttonSize, buttonSize };

	backButton = std::make_shared<Button>("Back To Menu", backTexture, srcRecBack, dstRecBack, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D retryTexture = LoadTexture("..\\..\\Assets\\Icons\\reset.png");
	Rectangle srcRecRetry = { 0.0f, 0.0f, (float)retryTexture.width, (float)retryTexture.height };
	Rectangle dstRecRetry = { 650.0f, GetScreenHeight() / 2.0f, buttonSize, buttonSize };

	retryButton = std::make_shared<Button>("Retry", retryTexture, srcRecRetry, dstRecRetry, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D resumeTexture = LoadTexture("..\\..\\Assets\\Icons\\play.png");
	Rectangle srcRecResume = { 0.0f, 0.0f, (float)resumeTexture.width, (float)resumeTexture.height };
	Rectangle dstRecResume = { GetScreenWidth() - 250.0f - buttonSize, GetScreenHeight() / 2.0f - 20.0f, buttonSize + 40.0f, buttonSize + 40.0f };

	resumeButton = std::make_shared<Button>("Resume", resumeTexture, srcRecResume, dstRecResume, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D quitTexture = LoadTexture("..\\..\\Assets\\Icons\\sign-out.png");
	Rectangle srcRecQuit = { 0.0f, 0.0f, (float)quitTexture.width, (float)quitTexture.height };
	Rectangle dstRecQuit = { GetScreenWidth() - 650.0f - buttonSize, GetScreenHeight() / 2.0f - 10.0f, buttonSize + 20.0f, buttonSize + 20.0f };

	quitButton = std::make_shared<Button>("Quit", quitTexture, srcRecQuit, dstRecQuit, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}

std::string WinModel::getTitle()
{
	return title;
}

std::shared_ptr<Button> WinModel::getQuitButton()
{
	return quitButton;
}

std::shared_ptr<Button> WinModel::getBackButton()
{
	return backButton;
}

std::shared_ptr<Button> WinModel::getRetryButton()
{
	return retryButton;
}

std::shared_ptr<Button> WinModel::getResumeButton()
{
	return resumeButton;
}