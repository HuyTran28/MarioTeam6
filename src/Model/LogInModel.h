#pragma once

#include <string>
#include <memory>
#include "StateModel.h"
#include <raylib.h>

class LogInModel : public StateModel
{
public:
	static float MAX_USERNAME_LENGTH;
	static float MAX_PASSWORD_LENGTH;
	static float BOX_WIDTH;
	static float BOX_HEIGHT;
	static float FONT_INPUT_SIZE;
	static float FONT_TITLE_SIZE;

	LogInModel();

	Rectangle getUsernameBox();
	Rectangle getPasswordBox();

	std::string getUsername();
	std::string getPassword();
	Texture2D& getBackground();

	void setUsername(std::string username);
	void setPassword(std::string password);

	bool checkCredentials(std::string username, std::string password);
private:
	std::string username;
	std::string password;

	Rectangle usernameBox;

	Rectangle passwordBox;

	Texture2D background;
	std::string backgroundPath;
};