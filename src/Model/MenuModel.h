#pragma once

#include "StateModel.h"
#include "PlayerData.h"
#include <string>
#include <vector>
#include <raylib.h>
#include <memory>

class MenuModel : public StateModel
{
private:
	std::shared_ptr<PlayerData> playerData;

	Camera3D camera;
	Vector3 cameraInitialPosition;


	Model lobbyModel;
	Vector3 lobbyPos;
	Vector3 lobbyScale;
	Vector3 lobbyRotationAxis;
	float lobbyRotationAngle;
	std::string lobbyModelPath;
	BoundingBox lobbyBoundingBox[8];
public:
	MenuModel();

	Camera3D& getCamera();
	void setCamera(Camera3D camera);

	std::shared_ptr<PlayerData> getPlayerData();
	void setPlayerData(std::shared_ptr<PlayerData> playerData);

	Model getLobbyModel();
	Vector3 getLobbyPos();
	Vector3 getLobbyScale();
	Vector3 getLobbyRotationAxis();
	float getLobbyRotationAngle();
	std::string getLobbyModelPath();
	BoundingBox* getLobbyBoundingBox();
	Vector3 getCameraInitialPosition();

};