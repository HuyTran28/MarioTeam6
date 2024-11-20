#pragma once
#include "Enemy.h"
#include "btBulletDynamicsCommon.h"

enum class EnemyType {
    Patrolling,
    Flying
};

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
        const Vector3& startPosition, const Vector3& forwardDir,
        float speed, float scale, float param1);
};
