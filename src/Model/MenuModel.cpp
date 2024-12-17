#include "MenuModel.h"


MenuModel::MenuModel() : StageModel(createMarioModel(Vector3{0.0f, 0.0f, 0.0f}, Vector3{3.0f, 3.0f, 3.0f}), Vector3{0.0f, 20.0f, 0.0f}, Vector3{-20.0f, 30.0f, 0.0f}, 60.0f, CAMERA_PERSPECTIVE, {}, {}, {})
{
    lobbyModelPath = "../../Assets\\Models\\Lobby\\lobby.glb";
    lobbyModel = LoadModel(lobbyModelPath.c_str());

    lobbyPos = Vector3{ 0.0f, 0.0f, 0.0f };
    lobbyScale = Vector3{ 0.1f, 0.1f, 0.1f };
    lobbyRotationAngle = 0.0f;
    lobbyRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };

	joyStickModelPath = "../../Assets\\Models\\joystick3.glb";
	joyStickModelPath2 = "../../Assets\\Models\\joystick2.glb";
	joystickModelLogIn = LoadModel(joyStickModelPath.c_str());
	joystickModelNoLogIn = LoadModel(joyStickModelPath2.c_str());
	joyStickPos = Vector3{ 110.0f, 10.0f, 10.0f };
	joyStickScale = Vector3{ 10.0f, 10.0f, 10.0f };
	joyStickRotationAngle = 180.0f;
	joyStickRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	joystickBoundingBox.min = Vector3{ joyStickPos.x, joyStickPos.y - 10.0f, joyStickPos.z - 6.8f };
	joystickBoundingBox.max = Vector3{ joyStickPos.x + 16.0f, joyStickPos.y + 9.0f, joyStickPos.z + 10.0f };

	std::string playerName = GameData::getInstance().getPlayerName();
	marioStatueModelPath = "../../Assets\\Models\\Characters\\" + playerName + ".glb";
	marioStatueScale = Vector3{ 10.0f, 10.0f, 10.0f };
	marioStatueRotationAngle = 225.0f;
	marioStatueModel = LoadModel(marioStatueModelPath.c_str());
	marioStatuePos = Vector3{ 80.0f, 0.0f, 40.0f };
	marioStatueRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	marioStatueBoundingBox.min = Vector3{ marioStatuePos.x - 7.0f, marioStatuePos.y, marioStatuePos.z - 15.0f };
	marioStatueBoundingBox.max = Vector3{ marioStatuePos.x + 12.0f, marioStatuePos.y + 35.0f, marioStatuePos.z + 7.0f };

	playModelPath = "../../Assets\\Models\\joystick.glb";	playModel = LoadModel(playModelPath.c_str());
	playPos = Vector3{ 110.0f, 0.0f, -20.0f };
	playScale = Vector3{ 1.0f, 1.0f, 1.0f };
	playRotationAngle = 180.0f;
	playRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playModelBoundingBox = GetModelBoundingBox(playModel);
	playModelBoundingBox.min = Vector3Add(playModelBoundingBox.min, playPos);
	playModelBoundingBox.max = Vector3Add(playModelBoundingBox.max, playPos);


	getPlayerData()->setMoveSpeed(1.0f);

    BoundingBox modelBox = GetModelBoundingBox(lobbyModel);

}

BoundingBox& MenuModel::getMarioStatueBoundingBox()
{
	return marioStatueBoundingBox;
}

BoundingBox& MenuModel::getJoystickBoundingBox()
{
	return joystickBoundingBox;
}

BoundingBox& MenuModel::getPlayModelBoundingBox()
{
	return playModelBoundingBox;
}

Model MenuModel::getJoyStickModelNoLogIn()
{
	return joystickModelNoLogIn;
}

Model MenuModel::getLobbyModel()
{
	return lobbyModel;
}

Vector3 MenuModel::getLobbyPos()
{
	return lobbyPos;
}

Vector3 MenuModel::getLobbyScale()
{
	return lobbyScale;
}

Vector3 MenuModel::getLobbyRotationAxis()
{
	return lobbyRotationAxis;
}

float MenuModel::getLobbyRotationAngle()
{
	return lobbyRotationAngle;
}

std::string MenuModel::getLobbyModelPath()
{
	return lobbyModelPath;
}

Model MenuModel::getJoyStickModel()
{
	return joystickModelLogIn;
}

Vector3 MenuModel::getJoyStickPos()
{
	return joyStickPos;
}

Vector3 MenuModel::getJoyStickScale()
{
	return joyStickScale;
}

Vector3 MenuModel::getJoyStickRotationAxis()
{
	return joyStickRotationAxis;
}

float MenuModel::getJoyStickRotationAngle()
{
	return joyStickRotationAngle;
}

std::string MenuModel::getJoyStickModelPath()
{
	return joyStickModelPath;
}

Model MenuModel::getMarioStatueModel()
{
	return marioStatueModel;
}

Vector3 MenuModel::getMarioStatuePos()
{
	return marioStatuePos;
}

Vector3 MenuModel::getMarioStatueScale()
{
	return marioStatueScale;
}

Vector3 MenuModel::getMarioStatueRotationAxis()
{
	return marioStatueRotationAxis;
}

float MenuModel::getMarioStatueRotationAngle()
{
	return marioStatueRotationAngle;
}

std::string MenuModel::getMarioStatueModelPath()
{
	return marioStatueModelPath;
}

Model MenuModel::getPlayModel()
{
	return playModel;
}

Vector3 MenuModel::getPlayPos()
{
	return playPos;
}

Vector3 MenuModel::getPlayScale()
{
	return playScale;
}

Vector3 MenuModel::getPlayRotationAxis()
{
	return playRotationAxis;
}

float MenuModel::getPlayRotationAngle()
{
	return playRotationAngle;
}

std::string MenuModel::getPlayModelPath()
{
	return playModelPath;
}






