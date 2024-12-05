#include "PatrollingEnemy.h"
#include "Koopa.h"
#include "EnemyFactory.h"
#include "raylib.h"
#include "memory.h"

Enemy* EnemyFactory::createEnemy(EnemyType type, btDiscreteDynamicsWorld* world, const std::string& modelPath,
    const Vector3& startPosition, const Vector3& forwardDir, float speed, float scale, EnemyAttributes* attributes)
{
    Model model = LoadModel(modelPath.c_str());
    BoundingBox modelBounds = GetModelBoundingBox(model);

    // Calculate the arm span (distance along the X-axis)
    float armSpan = (modelBounds.max.x - modelBounds.min.x) * scale;

    // Set the capsule radius to half the arm span
    float radius = armSpan * 0.5f - 0.2f;

    // Calculate height of the capsule based on the model's bounding box
    float height = (modelBounds.max.y - modelBounds.min.y) * scale; // Height of the model

    // Adjust height to exclude spherical parts of the capsule
    float capsuleHeight = height - radius;
    if (capsuleHeight < 0) {
        capsuleHeight = 0; // Prevent negative height
    }

    // Define initial transformation for the player
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create capsule shape
    btCollisionShape* collisionShape = new btCapsuleShape(radius, capsuleHeight);

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