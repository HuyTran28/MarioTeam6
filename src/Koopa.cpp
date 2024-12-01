#pragma once

#include "Enemy.h"
#include "Koopa.h"
#include "KoopaShellState.h"
#include "CollisionEvent.h"

Koopa::Koopa(btRigidBody* rigidBody, Model model, const Vector3& position,
    const Vector3& forwardDir, float speed, float scale,
    const Vector3& patrolPointA, const Vector3& patrolPointB, btDynamicsWorld* world)
    : PatrollingEnemy(rigidBody, model, position, forwardDir, speed, scale, patrolPointA, patrolPointB, world) {
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
    this->m_model = LoadModel("../../Assets/Models/Characters/KoopaShell.glb");
	m_scale = 0.5f;
	updateModelTransform();
}

void Koopa::recalculatePhysicsForShell() {
    // Remove the rigid body from the physics world if it exists
    if (m_dynamicsWorld && m_rigidBody) {
        m_dynamicsWorld->removeRigidBody(m_rigidBody);
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

    // Use the smallest axis for radius and the height for the capsule
    float radius = std::min(dimensions.x, dimensions.z) * 0.5f;
    float height = dimensions.y; // Use the full height of the model

    // Create a capsule collision shape (height is along the Y-axis in Bullet Physics)
    btCollisionShape* newShape = new btCapsuleShape(radius, height);

    // Recalculate mass and inertia
    btScalar shellMass = 30.0f;
    btVector3 shellInertia(0, 0, 0);
    newShape->calculateLocalInertia(shellMass, shellInertia);

    // Set up the rigid body construction info
    btDefaultMotionState* motionState = new btDefaultMotionState(currentTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(shellMass, motionState, newShape, shellInertia);

    // Delete the old rigid body and create a new one
    delete m_rigidBody;
    m_rigidBody = new btRigidBody(rbInfo);

    // Reapply the preserved position and orientation
    m_rigidBody->setWorldTransform(btTransform(currentRotation, currentPosition));

    // Reset velocities
    m_rigidBody->setLinearVelocity(btVector3(0, 0, 0));
    m_rigidBody->setAngularVelocity(btVector3(0, 0, 0));

    // Set damping factors
    m_rigidBody->setDamping(0.1f, 0.1f);

    // Set friction and restitution
    m_rigidBody->setFriction(0.1f);
	m_rigidBody->setRollingFriction(0.1f);
	m_rigidBody->setSpinningFriction(0.1f);

    m_rigidBody->setRestitution(0.2f); // Adjust for desired bounciness


    // Add the rigid body back to the physics world
    if (m_dynamicsWorld) {
        m_dynamicsWorld->addRigidBody(m_rigidBody);
    }

    m_rigidBody->setUserPointer(this);
}


