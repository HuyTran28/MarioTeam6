#pragma once
#include "../Model/Character/Enemy/Goomba.h"
#include "../Model/Character/Enemy/Koopa.h"
#include "../Model/ModelStage.h"

enum class EnemyType {
    Goomba,
    Koopa
};



class EnemyFactory 
{
public:
    static std::shared_ptr<Enemy> createEnemy(EnemyType type, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, const std::string& modelPath,
        const Vector3& startPosition, const Vector3& forwardDir, const Vector3& rotationAxis, const float& rotaionAngle, const Vector3& scale,
        const float& speed, const Vector3& pointA, const Vector3& pointB);
};