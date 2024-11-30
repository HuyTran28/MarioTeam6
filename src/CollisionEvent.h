#pragma once
#include "btBulletDynamicsCommon.h"
#include <vector>
#include "raylib.h"

class CharacterInterface;

enum class CollisionType {\
    Idle,
    Stomped,
    Kicked,
    HitByEnemy,
    // Add other collision types as needed
};

struct CollisionEvent {
    CharacterInterface* obj1;
    CharacterInterface* obj2;
    std::vector<btManifoldPoint> contactPoints;  // Store contact points from Bullet's collision

    CollisionType type;
    btVector3 kickDirection; // Relevant for Kicked collisions
};