#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
#include "../Model/Character/AnimationManager.h"



class StageController : public StateController
{

public:


	void updateCollisionShape(std::shared_ptr<PlayerData> playerData);
	void updateModelTransform(std::shared_ptr<PlayerData> playerData);
	bool checkGroundCollision(std::shared_ptr<PlayerData> playerData);


	void updateAnimationState(std::shared_ptr<PlayerData> marioData);
	void setPlayerAnimationState(std::shared_ptr<PlayerData> marioData);
	void updateMovementOfMario(std::shared_ptr<Mario> marioData);
	void moveMario(std::shared_ptr<Mario> marioData);
	void rotateMario(std::shared_ptr<Mario> marioData);
	void jumpMario(std::shared_ptr<Mario> marioData);



	void moveEnemy(std::shared_ptr<Enemy> enemyData);
	void moveToEnemy(std::shared_ptr<Enemy> enemyData);
	void rotateEnemy(std::shared_ptr<Enemy> enemyData);
	void updateMovemenOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies);



	void registerSelf() override;
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
};