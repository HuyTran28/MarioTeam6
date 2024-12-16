#include "SelectCharacter.h"

SelectCharacter::SelectCharacter()
{

	Texture2D backgroundTexture = LoadTexture("..\\..\\Assets\\Images\\BackgroundSelectCharacter.png");
	Rectangle srcRecBackground = { 0.0f, 0.0f, (float)backgroundTexture.width, (float)backgroundTexture.height };
	Rectangle destRecBackground = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
	background = std::make_shared<Button>("", backgroundTexture, srcRecBackground, destRecBackground, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);


	Texture2D backTexture = LoadTexture("..\\..\\Assets\\Icons\\back-arrow.png");
	Rectangle srcRecBack = { 0.0f, 0.0f, (float)backTexture.width, (float)backTexture.height };
	Rectangle destRecBack = { 50.0f, 50.0f, 100.0f, 100.0f };
	backButton = std::make_shared<Button>("", backTexture, srcRecBack, destRecBack, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	float height = 400.0f;
	float width = 400.0f;

	Texture2D marioTexture = LoadTexture("..\\..\\Assets\\Images\\Characters\\Mario.png");
	Rectangle srcRecMario = { 0.0f, 0.0f, (float)marioTexture.width, (float)marioTexture.height };
	Rectangle destRecMario = { 175.0f, GetScreenHeight() / 2.0f - height / 2.0f, width, height};
	std::shared_ptr<Button> marioButton = std::make_shared<Button>("Mario", marioTexture, srcRecMario, destRecMario, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D luigiTexture = LoadTexture("..\\..\\Assets\\Images\\Characters\\Luigi.png");
	Rectangle srcRecLuigi = { 0.0f, 0.0f, (float)luigiTexture.width, (float)luigiTexture.height };
	Rectangle destRecLuigi = { GetScreenWidth() / 2.0f - width / 2.0f, GetScreenHeight() / 2.0f - height / 2.0f, width, height };
	std::shared_ptr<Button> luigiButton = std::make_shared<Button>("Luigi", luigiTexture, srcRecLuigi, destRecLuigi, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D pricessTexture = LoadTexture("..\\..\\Assets\\Images\\Characters\\Princess.png");
	Rectangle srcRecPricess = { 0.0f, 0.0f, (float)pricessTexture.width, (float)pricessTexture.height };
	Rectangle destRecPricess = { GetScreenWidth() - 175.0f - width, GetScreenHeight() / 2.0f - height / 2.0f, width, height };
	std::shared_ptr<Button> pricessButton = std::make_shared<Button>("Princess", pricessTexture, srcRecPricess, destRecPricess, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);


	characterButtons.push_back(marioButton);
	characterButtons.push_back(luigiButton);
	characterButtons.push_back(pricessButton);
}

std::shared_ptr<Button> SelectCharacter::getBackground()
{
	return background;
}

std::vector<std::shared_ptr<Button>> SelectCharacter::getCharacterButtons()
{
	return characterButtons;
}

std::shared_ptr<Button> SelectCharacter::getBackButton()
{
	return backButton;
}

SelectCharacter::~SelectCharacter()
{

}

