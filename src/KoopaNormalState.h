#pragma once

#include "EnemyState.h"
#include "PatrollingEnemy.h"

class KoopaNormalState : public EnemyState {
public:
    void move(Enemy* enemy) override;
    void update(Enemy* enemy) override;
    void onCollision(Enemy* enemy, const CollisionEvent& event) override;
};
