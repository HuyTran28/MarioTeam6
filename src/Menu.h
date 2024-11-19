#pragma once

#include "Stage.h"
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "UI.h"
#include <iostream>

class Menu : public Stage
{
public:
	Menu();
	~Menu();
	void update() override;
	void draw() override;
private:
	void updateMovement();
	Camera3D camera;
	Vector3 cameraInitialPosition;

	Vector3 playerPosition;
	Model playerModel;
	BoundingBox playerBox;

	BoundingBox playButtonBox;
	BoundingBox exitButtonBox;


	Color playButtonColor;
	Color exitButtonColor;

	Color normalColor;
	Color hoverColor;
	Model lobbyModel;
	BoundingBox lobbyBox[8];
};



bool CheckCollisionRayBox(Ray ray, BoundingBox box);
