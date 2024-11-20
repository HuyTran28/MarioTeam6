#include "CharacterInterface.h"

const float CharacterInterface::GRAVITY = 9.8f;

CharacterInterface::CharacterInterface(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale, btDynamicsWorld* world)
    : m_rigidBody(rigidBody), m_model(model), m_position(position), m_forwardDir(forwardDir), 
      m_speed(speed), m_scale(scale), m_isOnGround(true), m_velocity({0.0f, 0.0f, 0.0f}),
       m_dynamicsWorld(world) {}

void CharacterInterface::render() {
    DrawModel(m_model, m_position, m_scale, WHITE);

    // Get the collision shape from the rigid body
    btCollisionShape* shape = m_rigidBody->getCollisionShape();
    
    btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
    btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();

    // Get the transform of the rigid body
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);

    // Convert Bullet's transform to your rendering library's format
    btVector3 origin = transform.getOrigin();
    btQuaternion rotation = transform.getRotation();

    // Draw the bounding box
    Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
    Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };
    Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

    //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
    DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
}

bool CharacterInterface::checkGroundCollision() {
    if (m_rigidBody) {
        // Get the current motion state of the rigid body
        btTransform transform;
        m_rigidBody->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 1.0f, 0); // Check 1 unit below the character

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        m_dynamicsWorld->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }

    return false;
}

