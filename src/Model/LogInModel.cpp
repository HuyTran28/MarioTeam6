#include "LogInModel.h"

int LogInModel::MAX_USERNAME_LENGTH = 20;
int LogInModel::MAX_PASSWORD_LENGTH = 20;
float LogInModel::BOX_WIDTH = 800;
float LogInModel::BOX_HEIGHT = 120;
float LogInModel::FONT_INPUT_SIZE = 40;
float LogInModel::FONT_TITLE_SIZE = 40;


LogInModel::LogInModel()
{
	usernameBox = { GetScreenWidth() / 2.0f - BOX_WIDTH / 2.0f, GetScreenHeight() / 2.0f - BOX_HEIGHT / 2.0f + 200.0f, BOX_WIDTH, BOX_HEIGHT };
	passwordBox = { GetScreenWidth() / 2.0f - BOX_WIDTH / 2.0f, GetScreenHeight() / 2.0f - BOX_HEIGHT / 2.0f + 400.0f, BOX_WIDTH, BOX_HEIGHT };
	backgroundPath = "..\\..\\Assets\\Images\\Thumbnail.png";
	background = LoadTexture(backgroundPath.c_str());
	isUsernameActive = false;
	isPasswordActive = false;
	isHidenPassword = true;
	failedLoginMessage = "Failed to log in. Please try again.";
	successLoginMessage = "Successfully logged in.";
	hidePassword = LoadTexture("..\\..\\Assets\\Icons\\show.png");
	showPassword = LoadTexture("..\\..\\Assets\\Icons\\eye.png");
	backArrow = LoadTexture("..\\..\\Assets\\Icons\\back-arrow.png");
	backArrowPosition = { 50.0f, 50.0f };
	backArrowScale = 0.2f;

	nextArrow = LoadTexture("..\\..\\Assets\\Icons\\next-arrow.png");
	nextArrowScale = 0.2f;
	nextArrowPosition = { GetScreenWidth() - nextArrow.width * nextArrowScale - 50.0f, 50.0f };

	hidePasswordScale = (float)passwordBox.height / (float)hidePassword.height;
	hidePasswordPosition = { passwordBox.x + passwordBox.width - hidePasswordScale * hidePassword.width, passwordBox.y};
}

bool LogInModel::checkCredentials(std::string username, std::string password)
{
	return false;
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

Texture2D& LogInModel::getBackArrow()
{
	return backArrow;
}

Vector2 LogInModel::getBackArrowPosition()
{
	return backArrowPosition;
}

float LogInModel::getBackArrowScale()
{
	return backArrowScale;
}

Texture2D& LogInModel::getNextArrow()
{
	return nextArrow;
}

Vector2 LogInModel::getNextArrowPosition()
{
	return nextArrowPosition;
}

float LogInModel::getNextArrowScale()
{
	return nextArrowScale;
}

std::string LogInModel::getFailedLoginMessage()
{
	return failedLoginMessage;
}

std::string LogInModel::getSuccessLoginMessage()
{
	return successLoginMessage;
}









