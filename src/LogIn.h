#pragma once

#include <raylib.h>
#include "Stage.h"
#include <string>
#include "Game.h"

class LogIn : public Stage
{
public:
    LogIn();
    ~LogIn();
    void update() override;
    void draw() override;

    static float boxWidth;
	static float boxHeight;
	static float fontInputSize;
	static float fontTitleSize;
private:
    std::string username;
    std::string password;

    bool usernameBoxFocused;
    bool passwordBoxFocused;

    Rectangle usernameBox;
    Rectangle passwordBox;

    int passwordLetterCount;
	int usernameLetterCount;
};
