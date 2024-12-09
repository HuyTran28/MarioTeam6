#pragma once

#include <string>
#include <memory>
#include "StateModel.h"
#include <raylib.h>

class LogInModel : public StateModel
{
public:
	static int MAX_USERNAME_LENGTH;
	static int MAX_PASSWORD_LENGTH;
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

	bool getUsernameActive();
	bool getPasswordActive();
	void setUsernameActive(bool active);
	void setPasswordActive(bool active);
	bool getIsHidenPassword();
	void setIsHidenPassword(bool isHidenPassword);
	Vector2 getHidePasswordPosition();
	Texture2D& getHidePassword();
	Texture2D& getShowPassword();
	float getHidePasswordScale();
private:
	std::string username;
	std::string password;

	Rectangle usernameBox;
	Rectangle passwordBox;

	Texture2D background;
	std::string backgroundPath;

	std::string failedLoginMessage;
	std::string successLoginMessage;

	Texture2D hidePassword;
	Texture2D showPassword;
	Vector2 hidePasswordPosition;
	bool isHidenPassword;
	float hidePasswordScale;

	bool isUsernameActive;
	bool isPasswordActive;

	Texture2D backArrow;
	Texture2D nextArrow;

};