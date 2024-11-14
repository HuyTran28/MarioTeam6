#pragma once

#include "Stage.h"
#include <string>
#include <raylib.h>
#include "raymath.h"
#include "UI.h"

class Menu : public Stage
{
public:
	Menu();
	~Menu();
	void update() override;
	void draw() override;
private:
	Camera3D camera;
	Rectangle playButton;
	Rectangle exitButton;
	Color playButtonColor;
	Color exitButtonColor;
	Color normalColor;
	Color hoverColor;
	Model lobbyModel;
	BoundingBox lobbyBox[8];

};
