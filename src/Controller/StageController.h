#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
#include "../Model/Character/AnimationManager.h"




class StageController : public StateController
{

public:


	void updateCollisionShape(std::shared_ptr<CharacterData> playerData);
	void updateModelTransform(std::shared_ptr<CharacterData> playerData);
	bool checkGroundCollision(std::shared_ptr<CharacterData> playerData);


	void updateAnimationState(std::shared_ptr<CharacterData> marioData);
	void setPlayerAnimationState(std::shared_ptr<CharacterData> marioData);
	void updateMovementOfPlayer(std::shared_ptr<PlayerData> marioData);
	void movePlayer(std::shared_ptr<PlayerData> marioData);
	void rotatePlayer(std::shared_ptr<PlayerData> marioData);
	void jumpPlayer(std::shared_ptr<PlayerData> marioData);



	void moveEnemy(std::shared_ptr<Enemy> enemyData);
	void moveToEnemy(std::shared_ptr<Enemy> enemyData);
	void rotateEnemy(std::shared_ptr<Enemy> enemyData);
	void updateMovemenOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies);



	void registerSelf() override;
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
};