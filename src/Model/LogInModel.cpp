#include "LogInModel.h"

int LogInModel::MAX_USERNAME_LENGTH = 20;
int LogInModel::MAX_PASSWORD_LENGTH = 20;
float LogInModel::BOX_WIDTH = 700;
float LogInModel::BOX_HEIGHT = 90;
float LogInModel::FONT_INPUT_SIZE = 40;
float LogInModel::FONT_TITLE_SIZE = 40;


LogInModel::LogInModel()
{
	usernameBox = { GetScreenWidth() / 2.0f - BOX_WIDTH / 2.0f, GetScreenHeight() / 2.0f - BOX_HEIGHT / 2.0f + 150.0f, BOX_WIDTH, BOX_HEIGHT };
	passwordBox = { GetScreenWidth() / 2.0f - BOX_WIDTH / 2.0f, GetScreenHeight() / 2.0f - BOX_HEIGHT / 2.0f + 350.0f, BOX_WIDTH, BOX_HEIGHT };
	backgroundPath = "..\\..\\Assets\\Images\\Thumbnail.png";
	background = LoadTexture(backgroundPath.c_str());
	isUsernameActive = false;
	isPasswordActive = false;
	isHidenPassword = true;
	failedLoginMessage = "Failed to log in. Please try again.";
	successLoginMessage = "Successfully logged in.";
	hidePassword = LoadTexture("..\\..\\Assets\\Icons\\show.png");
	showPassword = LoadTexture("..\\..\\Assets\\Icons\\eye.png");

	Texture2D backArrowTexture = LoadTexture("..\\..\\Assets\\Icons\\back-arrow.png");
	Rectangle srcRecBack = { 0.0f, 0.0f, (float)backArrowTexture.width, (float)backArrowTexture.height };
	Rectangle dstRecBack = { 50.0f, 50.0f, backArrowTexture.width * 0.2f, backArrowTexture.height * 0.2f };

	backArrow = std::make_shared<Button>("", backArrowTexture, srcRecBack, dstRecBack, Vector2{0.0f, 0.0f}, 0.0f, WHITE);

	Texture2D nextArrowTexture = LoadTexture("..\\..\\Assets\\Icons\\next-arrow.png");
	Rectangle srcRecNext = { 0.0f, 0.0f, (float)nextArrowTexture.width, (float)nextArrowTexture.height };
	Rectangle dstRecNext = { GetScreenWidth() - nextArrowTexture.width * 0.2f - 50.0f, 50.0f, nextArrowTexture.width * 0.2f, nextArrowTexture.height * 0.2f };

	nextArrow = std::make_shared<Button>("", nextArrowTexture, srcRecNext, dstRecNext, Vector2{0.0f, 0.0f}, 0.0f, WHITE);


	hidePasswordScale = (float)passwordBox.height / (float)hidePassword.height;
	hidePasswordPosition = { passwordBox.x + passwordBox.width - hidePasswordScale * hidePassword.width, passwordBox.y};
}

bool LogInModel::checkCredentials(std::string username, std::string password)
{
	return false;
}

std::shared_ptr<Button> LogInModel::getBackArrow()
{
	return backArrow;
}

std::shared_ptr<Button> LogInModel::getNextArrow()
{
	return nextArrow;
}

std::string LogInModel::getUsername()
{
	return username;
}

std::string LogInModel::getPassword()
{
	return password;
}

Rectangle LogInModel::getUsernameBox()
{
	return usernameBox;
}

Rectangle LogInModel::getPasswordBox()
{
	return passwordBox;
}

Texture2D& LogInModel::getBackground()
{
	return background;
}

void LogInModel::setUsername(std::string username)
{
	this->username = username;
}

void LogInModel::setPassword(std::string password)
{
	this->password = password;
}

bool LogInModel::getUsernameActive()
{
	return isUsernameActive;
}

bool LogInModel::getPasswordActive()
{
	return isPasswordActive;
}

void LogInModel::setUsernameActive(bool active)
{
	isUsernameActive = active;
}

void LogInModel::setPasswordActive(bool active)
{
	isPasswordActive = active;
}

bool LogInModel::getIsHidenPassword()
{
	return isHidenPassword;
}

void LogInModel::setIsHidenPassword(bool isHidenPassword)
{
	this->isHidenPassword = isHidenPassword;
}

Texture2D& LogInModel::getHidePassword()
{
	return hidePassword;
}

Vector2 LogInModel::getHidePasswordPosition()
{
	return hidePasswordPosition;
}

Texture2D& LogInModel::getShowPassword()
{
	return showPassword;
}

float LogInModel::getHidePasswordScale()
{
	return hidePasswordScale;
}

std::string LogInModel::getFailedLoginMessage()
{
	return failedLoginMessage;
}

std::string LogInModel::getSuccessLoginMessage()
{
	return successLoginMessage;
}









