#include "StageModel.h"
#include <iostream>
StageModel::StageModel()
{

    m_cameraInitialPosition = Vector3{ 300.0f, 20.0f, 20.0f };
    m_camera.position = m_cameraInitialPosition;
    m_camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    m_camera.fovy = 30.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

Camera3D& StageModel::getCamera()
{
    return m_camera;
}

void StageModel::setCamera(Camera3D camera)
{
    m_camera = camera;
}
