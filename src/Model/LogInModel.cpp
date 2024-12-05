#include "LogInModel.h"

float LogInModel::MAX_USERNAME_LENGTH = 20;
float LogInModel::MAX_PASSWORD_LENGTH = 20;
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





