#include "StageModel.h"
#include <iostream>
StageModel::StageModel(std::shared_ptr<PlayerData> playerData) : StageModel()
{
    m_playerData = playerData;
    initializeCamera();
}

StageModel::StageModel()
{
    m_cameraInitialPosition = Vector3{ 0.0f, 20.0f, 20.0f };
    m_camera.position = m_cameraInitialPosition;
    m_camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 30.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;

	Texture2D texture = LoadTexture("../../Assets/Icons/pause.png");
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = { 50.0f, 50.0f, 100.0f, 100.0f };
	m_pause = std::make_shared<Button>("", texture, sourceRec, destRec, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
	std::cout << "StageModel created" << std::endl;
}

Camera3D& StageModel::getCamera()
{
    return m_camera;
}

void StageModel::setCamera(Camera3D camera)
{
    m_camera = camera;
}

std::shared_ptr<PlayerData> StageModel::getPlayerData() const
{
    return m_playerData;
}

std::shared_ptr<Button> StageModel::getPauseButton() const
{
    return m_pause;
}

