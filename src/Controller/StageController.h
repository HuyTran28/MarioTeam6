#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
#include "../Model/Character/AnimationManager.h"
#include <cstdlib> 
#include <ctime>



class StageController : public StateController
{

public:
	void updateCollisionShape(std::shared_ptr<CharacterData> playerData);
	void updateModelTransform(std::shared_ptr<CharacterData> playerData);
	bool checkGroundCollision(std::shared_ptr<CharacterData> playerData);


	void updateAnimationState(std::shared_ptr<CharacterData> playerData);
	void setPlayerAnimationState(std::shared_ptr<CharacterData> playerData);
	void updateMovementOfPlayer(std::shared_ptr<PlayerData> playerData);
	void movePlayer(std::shared_ptr<PlayerData> playerData);
	void rotatePlayer(std::shared_ptr<PlayerData> playerData);
	void jumpPlayer(std::shared_ptr<PlayerData> playerData);

	void updateBigDuration(std::shared_ptr<PlayerData> playerData);

	void removeItem(std::vector<std::shared_ptr<ItemData>>& items, ItemData* item);

	void moveEnemy(std::shared_ptr<Enemy> enemyData);
	void moveToEnemy(std::shared_ptr<Enemy> enemyData);
	void rotateEnemy(std::shared_ptr<Enemy> enemyData);
	void updateMovemenOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies);

	void updateBounceOfBlock(std::shared_ptr<BlockData> blockData);


	void updateBlock(BlockData* preBlock, std::shared_ptr<BlockData> newBlock, std::vector<std::shared_ptr<BlockData>>& map, std::vector<std::shared_ptr<ItemData>>&itetms);

	void registerSelf() override;
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
};