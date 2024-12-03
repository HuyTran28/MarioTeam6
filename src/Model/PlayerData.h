#pragma once

#include <raylib.h>
#include <string>

class PlayerData
{
private:
	Vector3 playerPos;
	int playerHealth;
	Model playerModel;
	Vector3 playerScale;
	Vector3 playerRotationAxis;
	float playerRotationAngle;
	BoundingBox playerBoundingBox;
	std::string playerModelPath;
	float moveSpeed = 1.0f;
public:
	PlayerData();
	PlayerData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed);

	Vector3 getPlayerPos();
	int getPlayerHealth();
	Model getPlayerModel();
	BoundingBox getPlayerBoundingBox();
	Vector3 getPlayerScale();
	Vector3 getPlayerRotationAxis();
	float getPlayerRotationAngle();
	float getMoveSpeed();


	void setPlayerPos(Vector3 playerPos);
	void setPlayerHealth(int playerHealth);
	void setPlayerModel(Model playerModel);
	void setPlayerBoundingBox(BoundingBox playerBoundingBox);
	void setPlayerScale(Vector3 playerScale);
	void setPlayerRotationAxis(Vector3 playerRotationAxis);
	void setPlayerRotationAngle(float playerRotationAngle);
	void setMoveSpeed(float moveSpeed);

	~PlayerData();
};