#include "PlayerData.h"

PlayerData::PlayerData()
{
	//playerModelPath = "../../Assets\\Models\\Platforms\\Prop_Block_Brick.glb";
	playerModelPath = "../../Assets\\Models\\joystick2.glb";
	playerModel = LoadModel(playerModelPath.c_str());
	playerPos = Vector3{ 0.0f, 0.0f, 0.0f };
	playerHealth = 100;
	//playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
	playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
	playerRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playerRotationAngle = 0.0f;
	playerBoundingBox = GetModelBoundingBox(playerModel);
	moveSpeed = 1.0f;
}

PlayerData::~PlayerData()
{

}

Vector3 PlayerData::getPlayerPos()
{
	return playerPos;
}

int PlayerData::getPlayerHealth()
{
	return playerHealth;
}

Model PlayerData::getPlayerModel()
{
	return playerModel;
}

BoundingBox PlayerData::getPlayerBoundingBox()
{
	return playerBoundingBox;
}

Vector3 PlayerData::getPlayerScale()
{
	return playerScale;
}

Vector3 PlayerData::getPlayerRotationAxis()
{
	return playerRotationAxis;
}

float PlayerData::getPlayerRotationAngle()
{
	return playerRotationAngle;
}

float PlayerData::getMoveSpeed()
{
	return moveSpeed;
}

void PlayerData::setPlayerScale(Vector3 playerScale)
{
	this->playerScale = playerScale;
}

void PlayerData::setPlayerRotationAxis(Vector3 playerRotationAxis)
{
	this->playerRotationAxis = playerRotationAxis;
}

void PlayerData::setPlayerRotationAngle(float playerRotationAngle)
{
	this->playerRotationAngle = playerRotationAngle;
}

void PlayerData::setPlayerPos(Vector3 playerPos)
{
	this->playerPos = playerPos;
}

void PlayerData::setPlayerHealth(int playerHealth)
{
	this->playerHealth = playerHealth;
}

void PlayerData::setPlayerModel(Model playerModel)
{
	this->playerModel = playerModel;
}

void PlayerData::setPlayerBoundingBox(BoundingBox playerBoundingBox)
{
	this->playerBoundingBox = playerBoundingBox;
}

void PlayerData::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

PlayerData::PlayerData(Vector3 playerPos, int playerHealth, Model& playerModel, BoundingBox& playerBoundingBox, const std::string& playerModelPath, float moveSpeed)
{
	this->playerPos = playerPos;
	this->playerHealth = playerHealth;
	this->playerModel = playerModel;
	this->playerBoundingBox = playerBoundingBox;
	this->playerModelPath = playerModelPath;
	playerScale = Vector3{ 10.0f, 10.0f, 10.0f };
	playerRotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	playerRotationAngle = 0.0f;
	this->moveSpeed = moveSpeed;
}