#include "LogIn.h"

float LogIn::boxWidth = 800;
float LogIn::boxHeight = 120;
float LogIn::fontInputSize = 40;
float LogIn::fontTitleSize = 40;

LogIn::LogIn()
	: username(""), password(""), usernameBoxFocused(false), passwordBoxFocused(false), passwordLetterCount(0), usernameLetterCount(0)
{
    usernameBox = { Game::screenWidth / 2.0f - boxWidth / 2.0f, Game::screenHeight / 2.0f - boxHeight / 2.0f, boxWidth, boxHeight };
    passwordBox = { Game::screenWidth / 2.0f - boxWidth / 2.0f, Game::screenHeight / 2.0f - boxHeight / 2.0f + 200.0f, boxWidth, boxHeight };
}

LogIn::~LogIn()
{
}

void LogIn::update()
{
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, usernameBox))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            usernameBoxFocused = true;
            passwordBoxFocused = false;
        }
    }
    else if (CheckCollisionPointRec(mousePoint, passwordBox))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            passwordBoxFocused = true;
            usernameBoxFocused = false;
        }
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        usernameBoxFocused = false;
        passwordBoxFocused = false;
    }

    if (usernameBoxFocused)
    {
        int key = GetKeyPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (usernameLetterCount < 20))
            {
                username += (char)key;
                usernameLetterCount++;
            }
            key = GetKeyPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && usernameLetterCount > 0)
        {
            usernameLetterCount--;
            username.pop_back();
        }
    }

    if (passwordBoxFocused)
    {
        int key = GetKeyPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (passwordLetterCount < 20))
            {
                password += (char)key;
                passwordLetterCount++;
            }
            key = GetKeyPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && passwordLetterCount > 0)
        {
            passwordLetterCount--;
            password.pop_back();
        }
    }
}

void LogIn::draw()
{
    DrawText("Username:", usernameBox.x, usernameBox.y - 50.0f , fontTitleSize, DARKGRAY);
    DrawRectangleRec(usernameBox, LIGHTGRAY);
    DrawText(username.c_str(), usernameBox.x + fontInputSize, usernameBox.y + boxHeight / 2.0f - fontInputSize / 2.0f, fontInputSize, DARKGRAY);

    DrawText("Password:", passwordBox.x, passwordBox.y - 50.0f, fontTitleSize, DARKGRAY);
    DrawRectangleRec(passwordBox, LIGHTGRAY);
    DrawText(std::string(password.size(), '*').c_str(), passwordBox.x + fontInputSize, passwordBox.y + boxHeight / 2.0f - fontInputSize / 2.0f, fontInputSize, DARKGRAY);
}
