#pragma once
#include "Enemy.h"
#include "btBulletDynamicsCommon.h"

enum class EnemyType {
    Patrolling,
    Flying
};


class EnemyAttributes {
public:
	virtual ~EnemyAttributes() = default;
};

class PatrollingEnemyAttributes : public EnemyAttributes {
public:
    Vector3 point_A;
    Vector3 point_B;

	PatrollingEnemyAttributes(const Vector3& pointA, const Vector3& pointB)
		: point_A(pointA), point_B(pointB)
	{}
};

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
        const Vector3& startPosition,
        float speed, float scale, EnemyAttributes* attributes);
};
