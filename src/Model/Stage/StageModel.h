#pragma once

#include <raylib.h>
#include "../../Model/Block/BlockData.h"
#include "../../Model/Item/ItemData.h"
#include "../../Model/Character/Enemy/Enemy.h"
#include "../../Factory/BlockFactory.h"
#include "../../Factory/EnemyFactory.h"
#include "../../Factory/ItemFactory.h"
#include <vector>
#include "../StateModel.h"
#include "../../Model/Character/CharacterData.h"
#include "../../Button/Button.h"
#include "../../Model/Character/Player/PlayerData.h"
#include "../../CollisionManager/CollisionManager.h"






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
constexpr char PATH_ISLANDBLOCK[] = "../../Assets\\Models\\Platforms\\Flagpole.glb";
constexpr char PATH_WALLBLOCK1[] = "../../Assets\\Models\\Platforms\\WallBlock1.glb";
constexpr char PATH_WALLBLOCK2[] = "../../Assets\\Models\\Platforms\\WallBlock2.glb";
constexpr char PATH_WALLBLOCK3[] = "../../Assets\\Models\\Platforms\\WallBlock3.glb";
constexpr char PATH_WALLBLOCK4[] = "../../Assets\\Models\\Platforms\\WallBlock4.glb";
constexpr char PATH_WALLBLOCK5[] = "../../Assets\\Models\\Platforms\\WallBlock5.glb";
constexpr char PATH_GROUNDBLOCK[] = "../../Assets\\Models\\Platforms\\GroundBlock.glb";




constexpr char PATH_GOOMBA[] = "../../Assets\\Models\\Characters\\Goomba.glb";
constexpr char PATH_KOOPA[] = "../../Assets\\Models\\Characters\\Koopa.glb";
constexpr char PATH_BOWSER[] = "../../Assets\\Models\\Characters\\Bowser.glb";




constexpr char PATH_COIN[] = "../../Assets\\Models\\Items\\Coin.glb";
constexpr char PATH_REDMUSHROOM[] = "../../Assets\\Models\\Items\\RedMushroom.glb";
constexpr char PATH_PURPLEMUSHROOM[] = "../../Assets\\Models\\Items\\PurpleMushroom.glb";
constexpr char PATH_GREENMUSHROOM[] = "../../Assets\\Models\\Items\\GreenMushroom.glb";
constexpr char PATH_BOOMERANGFLOWER[] = "../../Assets\\Models\\Items\\BoomerangFlower.glb";
constexpr char PATH_BOOMERANG[] = "../../Assets\\Models\\Items\\Boomerang.glb";
constexpr char PATH_SUPPERSTAR[] = "../../Assets\\Models\\Items\\SuperStar.glb";










#include <iostream>
class StageModel : public StateModel
{
public:

	StageModel(Vector3 pos, Vector3 scale, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode);

	virtual ~StageModel() = default;
	StageModel(std::shared_ptr<PlayerData> playerData, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode,
		std::vector<std::shared_ptr<BlockData>> mapData, std::vector<std::shared_ptr<Enemy>> enemies, std::vector<std::shared_ptr<ItemData>> items);

	StageModel(Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode);


	Camera3D& getCamera();
	void setCamera(Camera3D camera);


	std::shared_ptr<PlayerData> getPlayerData() const;
	std::shared_ptr<Button> getPauseButton() const;

	std::shared_ptr<PlayerData> createMarioModel(Vector3 position, Vector3 scale);
	Vector3 getCameraInitialPosition() const {
		return m_cameraInitialPosition;
	}

	void setCameraInitialPosition(Vector3 cameraInitialPosition) {
		m_cameraInitialPosition = cameraInitialPosition;
	}

	std::vector<std::shared_ptr<Enemy>> getEnemies();
	void setEnemies(std::vector<std::shared_ptr<Enemy>> enemies);
	std::vector<std::shared_ptr<ItemData>> getItems();
	void setItems(std::vector<std::shared_ptr<ItemData>> items);
	std::vector<std::shared_ptr<BlockData>> getMap() const;
	void setMap(std::vector<std::shared_ptr<BlockData>> map);


	std::shared_ptr<Button> getSettingButton() const;
	std::shared_ptr<Button> getHealthButton() const;
	std::shared_ptr<Boomerang> getBoomerang() const;
	int getCoins() const;
	void setCoins(int coins);
	float getTimer();
	void setTimer(float timer);
	std::shared_ptr<Button> getTimerButton() const;
	int getScore() const;
	void setScore(int score);
protected:
	Camera3D m_camera;
	Vector3 m_cameraInitialPosition;

	int m_width;
	int m_depth;
	int m_height;


	int coins = 0;
	float timer = 300.0f;
	int score = 0;

	std::shared_ptr<PlayerData> m_playerData;
	std::vector<std::shared_ptr<BlockData>> m_map;
	std::vector <std::shared_ptr<Enemy>> m_enemies;
	std::vector<std::shared_ptr<ItemData>> m_items;
	std::shared_ptr<Boomerang> m_boomerang;


	std::shared_ptr<Button> m_pause;
	std::shared_ptr<Button> m_setting;
	std::shared_ptr<Button> m_health;
	std::shared_ptr<Button> m_timer;
};