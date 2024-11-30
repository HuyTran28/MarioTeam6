#pragma once
#include "CollisionEvent.h"

class Enemy;

class EnemyState {
public:
    virtual void move(Enemy* enemy) = 0;
    virtual void update(Enemy* enemy) = 0;
    virtual void onCollision(Enemy* enemy, const CollisionEvent& event) = 0;
    virtual ~EnemyState() = default;
};
