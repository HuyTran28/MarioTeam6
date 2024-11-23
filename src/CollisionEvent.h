#pragma once
#include "btBulletDynamicsCommon.h"
#include <vector>

class CharacterInterface;

struct CollisionEvent {
    CharacterInterface* obj1;
    CharacterInterface* obj2;
    std::vector<btManifoldPoint> contactPoints;  // Store contact points from Bullet's collision
};