#pragma once
#include <memory>
#include "StateController.h"
#include "../Model/Stage/StageModel.h"
#include "../Model/Character/AnimationManager.h"

class StageController : public StateController
{
protected:

public:
	void updateCollisionShape(std::shared_ptr<Mario> marioData);
	void updateModelTransform(std::shared_ptr<Mario> marioData);
	bool checkGroundCollision(std::shared_ptr<Mario> marioData);
	void playAnimation(int animationIndex);
	void updateAnimationState(std::shared_ptr<Mario> marioData);

	void registerSelf() override;
	void updateMovementOfMario(std::shared_ptr<Mario> marioData);
	void moveMario(std::shared_ptr<Mario> marioData);
	void rotateMario(std::shared_ptr<Mario> marioData);
	void jumpMario(std::shared_ptr<Mario> marioData);
	//void onCollision(const CollisionEvent& event);
	//void determineCollisionType(CollisionEvent& event);
};