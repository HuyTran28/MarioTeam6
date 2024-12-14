#pragma once

#include <raylib.h>
#include "../../Model/Block/BlockData.h"
#include "../../Factory/BlockFactory.h"
#include <vector>
#include "../StateModel.h"
#include "../../Model/Character/PlayerData.h"
#include "../../Button/Button.h"

constexpr char PATH_BRICKBLOCK[] = "../../Assets\\Models\\Platforms\\BrickBlock.glb";
constexpr char PATH_CASTLEBLOCK[] = "../../Assets\\Models\\Platforms\\CastleBlock.glb";
constexpr char PATH_MANMABLOCK[] = "../../Assets\\Models\\Platforms\\ManmaBlock.glb";
constexpr char PATH_NORMALBRICKBLOCK[] = "../../Assets\\Models\\Platforms\\NormalBrickBlock.glb";
constexpr char PATH_QUESTIONBLOCK[] = "../../Assets\\Models\\Platforms\\QuestionBlock.glb";
constexpr char PATH_PIPEBLOCK[] = "../../Assets\\Models\\Platforms\\PipeBlock.glb";
constexpr char PATH_EMPTYBLOCK[] = "../../Assets\\Models\\Platforms\\EmptyBlock.glb";
constexpr char PATH_ROULETTEBLOCK[] = "../../Assets\\Models\\Platforms\\RouletteBlock.glb";
constexpr char PATH_SUPPORTIVEPIPEBLOCK[] = "../../Assets\\Models\\Platforms\\SupportivePipeBlock.glb";
constexpr char PATH_FLYBLOCK[] = "../../Assets\\Models\\Platforms\\FlyBlock.glb";
constexpr char PATH_WATERBLOCK[] = "../../Assets\\Models\\Platforms\\WaterBlock.glb";


#include <iostream>
class StageModel : public StateModel
{
public:
	StageModel(std::shared_ptr<PlayerData> playerData);
	virtual ~StageModel() = default;
	StageModel();
	Camera3D& getCamera();
	void setCamera(Camera3D camera);
	std::shared_ptr<PlayerData> getPlayerData() const;
	std::shared_ptr<Button> getPauseButton() const;
private:
	Camera3D m_camera;
	Vector3 m_cameraInitialPosition;
	std::shared_ptr<PlayerData> m_playerData;
	std::shared_ptr<Button> m_pause;
	void initializeCamera() {
		m_cameraInitialPosition = m_playerData->getPlayerPos();
		m_camera.position = m_cameraInitialPosition;
		m_camera.target = m_playerData->getPlayerPos();
		m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
		m_camera.fovy = 45.0f;
		m_camera.projection = CAMERA_PERSPECTIVE;
	}
};