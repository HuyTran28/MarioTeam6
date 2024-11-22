#include "PatrollingEnemy.h"
#include "EnemyFactory.h"

#include "raylib.h"

Enemy* EnemyFactory::createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
    const Vector3& startPosition,
    float speed, float scale, EnemyAttributes* attributes) 
{

    // Load the enemy model first to get dimensions
    Model enemyModel = LoadModel(modelPath.c_str());
    BoundingBox modelBounds = GetModelBoundingBox(enemyModel);

    // Calculate dimensions for collision shape
    Vector3 dimensions = {
        (modelBounds.max.x - modelBounds.min.x),
        (modelBounds.max.y - modelBounds.min.y),
        (modelBounds.max.z - modelBounds.min.z)
    };

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create box shape based on model dimensions
    btCollisionShape* enemyShape = new btBoxShape(btVector3(
        dimensions.x * 0.3f,  // Half-extents
        dimensions.y * 0.4f,
        dimensions.z * 0.3f
    ));

    btScalar mass = 50.0f;
    btVector3 localInertia(0, 0, 0);
    enemyShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(
        btTransform(btQuaternion(0, 0, 0, 1), btVector3(startPosition.x, startPosition.y, startPosition.z))
    );
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, enemyShape, localInertia);

    btRigidBody* enemyRigidBody = new btRigidBody(rbInfo);

    // Add enemy to the world
    world->addRigidBody(enemyRigidBody);

    // Create enemy based on type
    switch (type) {
    case EnemyType::Patrolling:
    {
        auto patrollingAttributes = dynamic_cast<PatrollingEnemyAttributes*>(attributes);
        return new PatrollingEnemy(enemyRigidBody, enemyModel, startPosition, speed, scale, patrollingAttributes->point_A, patrollingAttributes->point_B);
    }
    default:
        return nullptr;

    }

    /*case EnemyType::Flying:
        return new FlyingEnemy(enemyRigidBody, enemyModel, forwardDir, startPosition, speed, scale, param1);*/

}