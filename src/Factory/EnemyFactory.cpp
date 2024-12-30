#include "EnemyFactory.h"

std::shared_ptr<Enemy> EnemyFactory::createEnemy(EnemyType type, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, const std::string& modelPath, const Vector3& startPosition,
    const Vector3& forwardDir, const Vector3& rotationAxis, const float& rotaionAngle, const Vector3& scale, const float& speed, const Vector3& pointA, const Vector3& pointB)
{

    auto it = ModelStage::listModels.find(modelPath);
    Model model = {};
    if (it != ModelStage::listModels.end()) {
        model = it->second;
    }
    else
    {
        model = LoadModel(modelPath.c_str());
        if (model.meshCount > 0)
        {
            ModelStage::listModels[modelPath] = model;
        }
    }

    BoundingBox modelBounds = GetModelBoundingBox(model);

    // Calculate the arm span (distance along the X-axis) and depth (Z-axis)
    float armSpan = (modelBounds.max.x - modelBounds.min.x) * scale.x;
    float depth = (modelBounds.max.z - modelBounds.min.z) * scale.z;

    // Set the capsule radius to a fraction of the smaller of armSpan and depth
    float radius = std::min(armSpan, depth) * 0.4f; // Adjust the multiplier for tighter fit

    // Calculate height of the capsule based on the model's bounding box
    float height = (modelBounds.max.y - modelBounds.min.y) * scale.y;

    // Adjust height to exclude spherical parts of the capsule
    float capsuleHeight = height - 2 * radius;
    if (capsuleHeight < 0) {
        capsuleHeight = 0; // Prevent negative height
    }

    // Define initial transformation for the player
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(startPosition.x, startPosition.y, startPosition.z));

    // Create capsule shape
    std::shared_ptr<btCollisionShape> collisionShape = std::make_shared<btCapsuleShape>(radius, capsuleHeight);

    btScalar mass = 20.0f;
    btVector3 localInertia(0, 0, 0);
    collisionShape->calculateLocalInertia(mass, localInertia);

    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(startTransform);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), collisionShape.get(), localInertia);

    std::shared_ptr<btRigidBody> rigidBody = std::make_shared <btRigidBody>(rbInfo);


    // Create enemy based on type
    switch (type)
    {
    case EnemyType::Goomba:
    {
        return std::make_shared<Goomba>(rigidBody, collisionShape, motionState, modelPath, pointA, forwardDir, pointA, pointB, speed, scale, rotationAxis, rotaionAngle, dynamicsWorld, "Goomba");

    }
    case EnemyType::Koopa:
    {
        return std::make_shared<Koopa>(rigidBody, collisionShape, motionState, modelPath, pointA, forwardDir, pointA, pointB, speed, scale, rotationAxis, rotaionAngle, dynamicsWorld, "Koopa");
    }
    case EnemyType::Bowser:
        return std::make_shared<Bowser>(rigidBody, collisionShape, motionState, modelPath, pointA, forwardDir, pointA, pointB, speed, scale, rotationAxis, rotaionAngle, dynamicsWorld, "Koopa");

    default:
        return nullptr;
    }
}
