#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
#include "../Model/Character/AnimationManager.h"
#include <cstdlib> 
#include <ctime>
#include "../Event/StateChangeEvent.h"
#include "../Button/Button.h"
#include "../Event/JumpEvent.h"
#include "../Event/DieEvent.h"
#include "../Event/BoomerangEvent.h"
#include "../Event/EnemyDie.h"

class StageController : public StateController
{
public:
	void updateCollisionShape(std::shared_ptr<CharacterData> playerData);
	void updateModelTransform(std::shared_ptr<CharacterData> playerData);
	bool checkGroundCollision(std::shared_ptr<CharacterData> playerData);


	void updateAnimationState(std::shared_ptr<CharacterData> playerData, Camera3D cam);
	void setPlayerAnimationState(std::shared_ptr<CharacterData> playerData);
	void updateMovementOfPlayer(std::shared_ptr<PlayerData> playerData, Camera3D cam);
	void movePlayer(std::shared_ptr<PlayerData> playerData);
	void jumpPlayer(std::shared_ptr<PlayerData> playerData);

	void updateBigDuration(std::shared_ptr<PlayerData> playerData);
	void updateSpecial(std::shared_ptr<PlayerData> playerData);
	void updatePauseAndSetting(std::shared_ptr<Button> setting, std::shared_ptr<Button> pause);
	void removeItem(std::vector<std::shared_ptr<ItemData>>& items, ItemData* item);
	void removeEnemy(std::vector<std::shared_ptr<Enemy>>& enemies, Enemy* enemy);

	void updatePlayerDie(std::shared_ptr<PlayerData> playerData);

	void moveEnemy(std::shared_ptr<Enemy> enemyData, std::shared_ptr<PlayerData> playerData);
	void moveToEnemy(std::shared_ptr<Enemy> enemyData);
	void rotateEnemy(std::shared_ptr<Enemy> enemyData);
	void updateMovementOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies, Camera3D cam, std::shared_ptr<PlayerData> playerData);


	void updateMovementOfBoomerang(std::shared_ptr<Boomerang> boomerang);
	void updateTimeBoomerang(std::shared_ptr<PlayerData> playerData, std::shared_ptr<Boomerang> boomerang);


	void updateBounceOfBlock(std::shared_ptr<BlockData> blockData);
	void updateInvincibilityTimer(std::shared_ptr<PlayerData> playerData);
	void updateTimer(float& timer);
	void updateBlock(BlockData* preBlock, std::shared_ptr<BlockData> newBlock, std::vector<std::shared_ptr<BlockData>>& map, std::vector<std::shared_ptr<ItemData>>&itetms);
	void updateScore(std::shared_ptr<Event> event, std::shared_ptr<StageModel> model);
	void registerSelf() override;

	void updateCamera(std::shared_ptr<StageModel> model);
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
protected:
	bool isNotifyDie = false;
	bool isInputEnable = true;
};