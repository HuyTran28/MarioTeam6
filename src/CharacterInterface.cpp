#include "CharacterInterface.h"
#include <algorithm>

CharacterInterface::CharacterInterface(btRigidBody* rigidBody, Model model, const Vector3& position,
    const float& speed, const float& scale, btDynamicsWorld* world)
    : m_rigidBody(rigidBody), m_model(model), m_position(position), 
      m_speed(speed), m_scale(scale), m_isOnGround(true), m_velocity({0.0f, 0.0f, 0.0f}),
      m_dynamicsWorld(world), m_rotationAngle(0.0f) 
{
    btTransform trans;
    m_rigidBody->getMotionState()->getWorldTransform(trans);

    btVector3 physicalPosition = trans.getOrigin();
    m_position = { physicalPosition.x(), physicalPosition.y(), physicalPosition.z() };
	// Set the rigid body's user pointer to this character
	m_rigidBody->setUserPointer(this);
	m_rigidBody->setGravity(btVector3(0, -9.81 * m_rigidBody->getMass(), 0));
}

void CharacterInterface::render() {
    DrawModel(m_model, m_position, m_scale, WHITE);

    // Get the collision shape from the rigid body
    btCollisionShape* shape = m_rigidBody->getCollisionShape();

    // Get the transform of the rigid body
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);

    // Convert Bullet's transform to your rendering library's format
    btVector3 origin = transform.getOrigin();
    btQuaternion rotation = transform.getRotation();
    Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
    Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };

    if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
        btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
        btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
        Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

        //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
        DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
    }
    else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
        btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(shape);

        // Get the bounding box of the model
        BoundingBox modelBounds = GetModelBoundingBox(m_model);
        float modelHeight = (modelBounds.max.y - modelBounds.min.y) * m_scale;
        float modelRadius = std::max((modelBounds.max.x - modelBounds.min.x), (modelBounds.max.z - modelBounds.min.z)) * m_scale / 2.0f;

        // Adjust the capsule size to wrap around the model
        float radius = modelRadius * 1.1f; // Slightly larger than the model radius
        float halfHeight = (modelHeight / 2.0f) - radius;

        Vector3 startPos = { boxPosition.x, boxPosition.y - halfHeight, boxPosition.z };
        Vector3 endPos = { boxPosition.x, boxPosition.y + halfHeight, boxPosition.z };
        //DrawCapsule(startPos, endPos, radius, RED); // Draw the capsule in red
        DrawCapsuleWires(startPos, endPos, radius, 16, 16, BLACK); // Draw the capsule wireframe in black
    }
    // Add handling for other shape types here
    else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
        btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
        float radius = sphereShape->getMargin(); // Assuming margin is the radius
        //DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
        DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
    }
    // Add more shape types as needed
}

bool CharacterInterface::checkGroundCollision() {
    if (m_rigidBody) {
        // Get the current motion state of the rigid body
        btTransform transform;
        m_rigidBody->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 2.0f, 0);

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        m_dynamicsWorld->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }

    return false;
}

void CharacterInterface::updateCollisionShape() {
    // Get the rigid body's current transform
    btTransform transform = m_rigidBody->getWorldTransform();

    // Reset the rotation to identity to keep the capsule upright
    transform.setRotation(btQuaternion(0, 0, 0, 1));

    // Update the rigid body's transformation
    m_rigidBody->setWorldTransform(transform);
    m_rigidBody->getMotionState()->setWorldTransform(transform);

    // Ensure the rigid body is active
    m_rigidBody->activate(true);
}



void CharacterInterface::updateModelTransform() {
    // Get the rigid body's transform
    btTransform transform = m_rigidBody->getWorldTransform();
    btVector3 origin = transform.getOrigin();

    // Get the bounding box of the model
    BoundingBox modelBounds = GetModelBoundingBox(m_model);
    float modelHeight = (modelBounds.max.y - modelBounds.min.y) * m_scale;

    // Retrieve the collision shape and calculate capsule dimensions
    btCollisionShape* collisionShape = m_rigidBody->getCollisionShape();
    btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
    float capsuleRadius = capsuleShape->getRadius();
    float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

    // Calculate the vertical offset to align the model's center with the capsule's center
    float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (modelHeight / 2);

    // Update the model position
    m_position = { origin.getX(), origin.getY() + yOffset, origin.getZ() };

    // Apply rotation and scale to the model
    Matrix rotationMatrix = MatrixRotateY(m_rotationAngle);
    Matrix scaleMatrix = MatrixScale(m_scale, m_scale, m_scale);

    // Combine the transformations and apply to the model
    m_model.transform = MatrixMultiply(scaleMatrix, rotationMatrix);
}





CharacterInterface::~CharacterInterface()
{
    // Remove the rigid body from the dynamics world
    if (m_dynamicsWorld && m_rigidBody) {
        m_dynamicsWorld->removeRigidBody(m_rigidBody);
    }

    // Delete the collision shape
    btCollisionShape* shape = m_rigidBody->getCollisionShape();
    delete shape;

    // Delete the motion state
    btMotionState* motionState = m_rigidBody->getMotionState();
    delete motionState;

    // Delete the rigid body
    delete m_rigidBody;
}