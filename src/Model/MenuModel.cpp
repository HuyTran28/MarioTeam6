#include "MenuModel.h"

MenuModel::MenuModel()
{
	playerData = std::make_shared<PlayerData>();

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

	marioStatueModelPath = "../../Assets\\Models\\Princess Peach\\Peach2.glb";
	marioStatueModel = LoadModel(marioStatueModelPath.c_str());
	marioStatuePos = Vector3{ 80.0f, 0.0f, 40.0f };
	marioStatueScale = Vector3{ 0.25f, 0.25f, 0.25f };
	marioStatueRotationAngle = 225.0f;
	marioStatueRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };

	playModelPath = "../../Assets\\Models\\joystick.glb";
	playModel = LoadModel(playModelPath.c_str());
	playPos = Vector3{ 110.0f, 0.0f, -20.0f };
	playScale = Vector3{ 1.0f, 1.0f, 1.0f };
	playRotationAngle = 180.0f;
	playRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playModelBoundingBox = GetModelBoundingBox(playModel);
	playModelBoundingBox.min = Vector3Add(playModelBoundingBox.min, playPos);
	playModelBoundingBox.max = Vector3Add(playModelBoundingBox.max, playPos);


    cameraInitialPosition = Vector3{ 0.0f, 20.0f, 0.0f };
    camera.position = cameraInitialPosition;
    camera.target = Vector3{ -20.0f, 30.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    BoundingBox modelBox = GetModelBoundingBox(lobbyModel);
    this->playerData = playerData;
    // Left wall
    lobbyBoundingBox[0] = BoundingBox{
        Vector3{ modelBox.min.x , modelBox.min.y, modelBox.min.z },
        Vector3{ modelBox.min.x, modelBox.max.y + 4000.0f, modelBox.max.z }
    };

    // Right wall
    lobbyBoundingBox[1] = BoundingBox{
        Vector3{ modelBox.max.x - 70.0f, modelBox.min.y, modelBox.min.z },
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f, modelBox.max.z }
    };

    // Front wall
    lobbyBoundingBox[2] = BoundingBox{
        Vector3{ modelBox.min.x, modelBox.min.y, modelBox.min.z + 30.0f },
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f, modelBox.min.z }
    };

    lobbyBoundingBox[4] = modelBox;
    lobbyBoundingBox[4].max.x -= 450.0f;
    lobbyBoundingBox[4].min.x += 450.0f;

    lobbyBoundingBox[5] = modelBox;
    lobbyBoundingBox[5].max.z -= 400.0f;
    lobbyBoundingBox[5].min.z += 400.0f;

    // Back wall
    lobbyBoundingBox[3] = BoundingBox{
        Vector3{ modelBox.min.x, modelBox.min.y, modelBox.max.z - 70.0f},
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f , modelBox.max.z }
    };
    lobbyBoundingBox[6] = BoundingBox{
        Vector3{ modelBox.max.x - 2300.0f, modelBox.max.y, modelBox.max.z - 1000.0f},
        Vector3{ modelBox.max.x - 1800.0f, modelBox.max.y + 600.0f, modelBox.min.z + 250.0f }
    };

    lobbyBoundingBox[7] = BoundingBox{
        Vector3{ modelBox.max.x - 1800.0f, modelBox.max.y + 400.0f, modelBox.max.z - 1000.0f},
        Vector3{ modelBox.max.x - 1400.0f, modelBox.max.y + 600.0f, modelBox.min.z + 250.0f }
    };
}

Camera3D& MenuModel::getCamera()
{
	return camera;
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


std::shared_ptr<PlayerData> MenuModel::getPlayerData()
{
	return playerData;
}

void MenuModel::setPlayerData(std::shared_ptr<PlayerData> playerData)
{
	this->playerData = playerData;
}

void MenuModel::setCamera(Camera3D camera)
{
	this->camera = camera;
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

BoundingBox* MenuModel::getLobbyBoundingBox()
{
	return lobbyBoundingBox;
}

Vector3 MenuModel::getCameraInitialPosition()
{
	return cameraInitialPosition;
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






