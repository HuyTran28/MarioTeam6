#pragma once

#include "Enemy.h"
#include "Koopa.h"
#include "KoopaShellState.h"
#include "CollisionEvent.h"

Koopa::Koopa(btRigidBody* rigidBody, std::string modelPath, const Vector3& position,
    const Vector3& forwardDir, float speed, float scale,
    const Vector3& patrolPointA, const Vector3& patrolPointB, btDynamicsWorld* world)
    : PatrollingEnemy(rigidBody, modelPath, position, forwardDir, speed, scale, patrolPointA, patrolPointB, world) {
    setState(std::make_unique<KoopaNormalState>());
}

void Koopa::move() {
	m_currentState->move(this);
}

void Koopa::onCollision(const CollisionEvent& event)
{
	m_currentState->onCollision(this, event);
}

void Koopa::changeToShellModel() {
    // Load or switch to the shell model
    UnloadModel(this->m_model);
    this->m_model = LoadModel("Assets/Models/Characters/KoopaShell.glb");
	m_scale = 0.5f;
	updateModelTransform();
}

void Koopa::recalculatePhysicsForShell() {
    if (m_rigidBody == nullptr || m_dynamicsWorld == nullptr) {
        return; // Safety check
    }

    // Preserve the current transform
    btTransform currentTransform = m_rigidBody->getWorldTransform();
    btVector3 currentPosition = currentTransform.getOrigin();
    btQuaternion currentRotation = currentTransform.getRotation();

    // Load the model to get dimensions
    BoundingBox modelBounds = GetModelBoundingBox(m_model);

    // Calculate dimensions for collision shape
    Vector3 dimensions = {
        (modelBounds.max.x - modelBounds.min.x) * m_scale,
        (modelBounds.max.y - modelBounds.min.y) * m_scale,
        (modelBounds.max.z - modelBounds.min.z) * m_scale
    };

    // Calculate capsule dimensions
    float radius = std::min(dimensions.x, dimensions.z) * 0.5f; // Smallest dimension in X/Z
    float height = dimensions.y - 2.0 * radius; // Subtract spherical caps

    if (height < 0) {
        height = 0; // Ensure height is non-negative, in case dimensions are spherical
    }

    // Create a new capsule collision shape (height is along the Y-axis in Bullet Physics)
    btCollisionShape* newShape = new btCapsuleShape(radius, height);

    // Recalculate mass and inertia
    btScalar shellMass = 50.0f;
    btVector3 shellInertia(0, 0, 0);
    newShape->calculateLocalInertia(shellMass, shellInertia);

    // Update the rigid body
    m_rigidBody->setCollisionShape(newShape);
    m_rigidBody->setMassProps(shellMass, shellInertia);

    // Reapply preserved position and orientation
    m_rigidBody->setWorldTransform(btTransform(currentRotation, currentPosition));

    // Reset velocities
    m_rigidBody->setLinearVelocity(btVector3(0, 0, 0));
    m_rigidBody->setAngularVelocity(btVector3(0, 0, 0));

    // Set damping, friction, and restitution
    m_rigidBody->setDamping(0.1f, 0.1f);
    m_rigidBody->setFriction(0.5f);
    m_rigidBody->setRollingFriction(0.5f);
    m_rigidBody->setSpinningFriction(0.5f);
    m_rigidBody->setRestitution(0.2f);

    // Update user pointer
    m_rigidBody->setUserPointer(this);
}




