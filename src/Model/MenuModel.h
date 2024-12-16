#pragma once

#include "Stage/StageModel.h"
#include "../Model/Character/CharacterData.h"
#include "../Model/Character/Player/PlayerData.h"
#include <string>
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <memory>

class MenuModel : public StageModel
{
private:
	Model lobbyModel;
	Vector3 lobbyPos;
	Vector3 lobbyScale;
	Vector3 lobbyRotationAxis;
	float lobbyRotationAngle;
	std::string lobbyModelPath;

	Model joystickModelLogIn;
	Model joystickModelNoLogIn;
	Vector3 joyStickPos;
	Vector3 joyStickScale;
	Vector3 joyStickRotationAxis;
	float joyStickRotationAngle;
	std::string joyStickModelPath;
	std::string joyStickModelPath2;
	BoundingBox joystickBoundingBox;


	Model marioStatueModel;
	Vector3 marioStatuePos;
	Vector3 marioStatueScale;
	Vector3 marioStatueRotationAxis;
	float marioStatueRotationAngle;
	std::string marioStatueModelPath;

	Model playModel;
	Vector3 playPos;
	Vector3 playScale;
	Vector3 playRotationAxis;
	float playRotationAngle;
	std::string playModelPath;
	BoundingBox playModelBoundingBox;

public:
	MenuModel();

	Model getLobbyModel();
	Vector3 getLobbyPos();
	Vector3 getLobbyScale();
	Vector3 getLobbyRotationAxis();
	float getLobbyRotationAngle();
	std::string getLobbyModelPath();
	Model getJoyStickModel();
	Model getJoyStickModelNoLogIn();
	Vector3 getJoyStickPos();
	Vector3 getJoyStickScale();
	Vector3 getJoyStickRotationAxis();
	float getJoyStickRotationAngle();
	std::string getJoyStickModelPath();
	Model getMarioStatueModel();
	Vector3 getMarioStatuePos();
	Vector3 getMarioStatueScale();
	Vector3 getMarioStatueRotationAxis();
	float getMarioStatueRotationAngle();
	std::string getMarioStatueModelPath();
	Model getPlayModel();
	Vector3 getPlayPos();
	Vector3 getPlayScale();
	Vector3 getPlayRotationAxis();
	float getPlayRotationAngle();
	std::string getPlayModelPath();
	BoundingBox& getJoystickBoundingBox();
	BoundingBox& getPlayModelBoundingBox();
};