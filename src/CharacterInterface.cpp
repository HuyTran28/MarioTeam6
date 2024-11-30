#include "CharacterInterface.h"
#include <algorithm>

const float CharacterInterface::GRAVITY = 9.8f;

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
        btVector3 end = start - btVector3(0, 1.5f, 0); // Check 1 unit below the character

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
	// Update the collision shape's scale based on the model's scale
	btVector3 bulletScale(m_scale, m_scale, m_scale);
	m_rigidBody->getCollisionShape()->setLocalScaling(bulletScale);

	// Create a new transformation for the collision shape
	btTransform transform;
	transform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	// Convert the model's rotation matrix into a Bullet quaternion
	Matrix rotationMatrix = MatrixRotateY(m_rotationAngle); // Assumes Y-axis rotation
	Quaternion modelQuaternion = QuaternionFromMatrix(rotationMatrix);
	transform.setRotation(btQuaternion(modelQuaternion.x, modelQuaternion.y, modelQuaternion.z, modelQuaternion.w));

	// Update the rigid body's transformation
	m_rigidBody->setWorldTransform(transform);
	m_rigidBody->getMotionState()->setWorldTransform(transform);

	// Activate the rigid body to ensure changes take effect
	m_rigidBody->activate(true);
}

void CharacterInterface::updateModelTransform() {
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);

    BoundingBox modelBounds = GetModelBoundingBox(m_model);
    btCollisionShape* shape = m_rigidBody->getCollisionShape();
    float minY = modelBounds.min.y;

    if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
        btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
        btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
        minY = halfExtents.getY();
    } else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
       
    }

    btVector3 origin = transform.getOrigin();
    float yOffset = modelBounds.min.y * m_scale - minY;
    m_position = { origin.getX(), origin.getY() + yOffset, origin.getZ() };

    // Update the model's rotation
    btQuaternion rotation = transform.getRotation();
    Quaternion modelRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };
    /*m_model.transform = QuaternionToMatrix(modelRotation);*/

     // Apply scaling to the transformation matrix
    Matrix scaleMatrix = MatrixScale(m_scale, m_scale, m_scale);
    Matrix rotationMatrix = QuaternionToMatrix(modelRotation);
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