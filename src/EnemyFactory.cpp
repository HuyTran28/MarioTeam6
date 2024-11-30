#include "PatrollingEnemy.h"
#include "Koopa.h"
#include "EnemyFactory.h"
#include "raylib.h"
#include "memory.h"

Enemy* EnemyFactory::createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
    const Vector3& startPosition, const Vector3& forwardDir, float speed, float scale, EnemyAttributes* attributes)
{
    // Load the player model first to get dimensions
    Model model = LoadModel(modelPath.c_str());
    BoundingBox modelBounds = GetModelBoundingBox(model);

    // Calculate dimensions for collision shape
    Vector3 dimensions = {
        (modelBounds.max.x - modelBounds.min.x) * scale,
        (modelBounds.max.y - modelBounds.min.y) * scale,
        (modelBounds.max.z - modelBounds.min.z) * scale
    };

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create box shape based on model dimensions
    btCollisionShape* collisionShape = new btBoxShape(btVector3(
        dimensions.x * 0.5f,  // Half-extents
        dimensions.y * 0.5f,
		dimensions.z * 0.5f
    ));

    btScalar mass = 50.0f;
    btVector3 localInertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collisionShape, localInertia);

    btRigidBody* rigidBody = new btRigidBody(rbInfo);

    // Add player to the world
    world->addRigidBody(rigidBody);

    // Create enemy based on type
    switch (type) {
    case EnemyType::Patrolling:
    {
        auto patrollingAttributes = dynamic_cast<PatrollingEnemyAttributes*>(attributes);
        return new PatrollingEnemy(rigidBody, model, startPosition, forwardDir, speed, scale, patrollingAttributes->point_A, patrollingAttributes->point_B, world);
    }
	case EnemyType::Koopa:
    {
        auto patrollingAttributes = dynamic_cast<PatrollingEnemyAttributes*>(attributes);
        return new Koopa(rigidBody, model, startPosition, forwardDir, speed, scale, patrollingAttributes->point_A, patrollingAttributes->point_B, world);

    }
    default:
        return nullptr;
    }
}