#include "EnemyFactory.h"
#include "PatrollingEnemy.h"
#include "raylib.h"

Enemy* EnemyFactory::createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
    const Vector3& startPosition, const Vector3& forwardDir,
    float speed, float scale, float param1) {
    
    // Load the model
    Model enemyModel = LoadModel(modelPath.c_str());

    // Calculate the bounding box of the model
    BoundingBox bbox = GetModelBoundingBox(enemyModel);

    // Calculate the dimensions of the bounding box
    float width = bbox.max.x - bbox.min.x;
    float height = bbox.max.y - bbox.min.y;
    float depth = bbox.max.z - bbox.min.z;

    // Shared Bullet Physics setup
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create the collision shape based on the bounding box dimensions
    btCollisionShape* enemyShape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
    btScalar mass = 50.0f;
    btVector3 localInertia(0, 0, 0);
    enemyShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, enemyShape, localInertia);

    btRigidBody* enemyRigidBody = new btRigidBody(rbInfo);
    world->addRigidBody(enemyRigidBody);

    // Create enemy based on type
    /*switch (type) {
    case EnemyType::Patrolling:
        return new PatrollingEnemy(enemyRigidBody, enemyModel, forwardDir, startPosition, speed, scale, param1);

    case EnemyType::Flying:
        return new FlyingEnemy(enemyRigidBody, enemyModel, forwardDir, startPosition, speed, scale, param1);

    default:
        return nullptr;
    }*/
    return nullptr;
}
