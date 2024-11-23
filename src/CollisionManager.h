#pragma once
#include "CharacterInterface.h"
#include "btBulletDynamicsCommon.h"
#include <vector>

#include "CollisionEvent.h"

class CollisionManager {
private:
	btDynamicsWorld* dynamicsWorld;

public:
	CollisionManager(btDynamicsWorld* world);

	void detectCollisions();
	void dispatch(const CollisionEvent& event);
};