#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
class StageController : public StateController
{
protected:
	//std::shared_ptr<StageModel> model;
	//std::shared_ptr<PlayerData> playerData;
public:
	//StageController(std::shared_ptr<Mario> mario) : marioModel(mario){}

	void updateCollisionShape(std::shared_ptr<Mario> marioData);
	void updateModelTransform(std::shared_ptr<Mario> marioData);
	bool checkGroundCollision(std::shared_ptr<Mario> marioData);
	void playAnimation(int animationIndex);


	void registerSelf() override;
	void updateMovementOfMario(std::shared_ptr<Mario> marioData);
	void moveMario(std::shared_ptr<Mario> marioData);
	void rotateMario(std::shared_ptr<Mario> marioData);
	void jumpMario(std::shared_ptr<Mario> marioData);
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
};