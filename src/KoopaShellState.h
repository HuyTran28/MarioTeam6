#pragma once

#include "EnemyState.h"

class KoopaShellState : public EnemyState {
public:
    void move(Enemy* enemy) override;
    void update(Enemy* enemy) override;
    void onCollision(Enemy* enemy, const CollisionEvent& event) override;
};
