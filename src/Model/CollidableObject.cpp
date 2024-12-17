#include "CollidableObject.h"

CollidableObject::CollidableObject()
{
	objectType = "CollidableObject";
}

CollidableObject::CollidableObject(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::shared_ptr<btDynamicsWorld> world)
{
	m_rigidBody = rigidBody;
	m_collisionShape = shape;
	m_motionState = motionState;
	m_dynamicsWorld = world;
	m_rigidBody->setUserPointer(this);
	objectType = "CollidableObject";
}

std::string CollidableObject::getObjectType()
{
	return objectType;
}

std::shared_ptr<btRigidBody> CollidableObject::getRigidBody() const
{
	return m_rigidBody;
}

std::shared_ptr<btDynamicsWorld> CollidableObject::getDynamicsWorld() const
{
	return m_dynamicsWorld;
}

std::shared_ptr<btCollisionShape> CollidableObject::getCollisionShape() const
{
	return m_collisionShape;
}

std::shared_ptr<btDefaultMotionState> CollidableObject::getMotionState() const
{
	return m_motionState;
}

void CollidableObject::setRigidBody(std::shared_ptr<btRigidBody> rigidBody)
{
	m_rigidBody = rigidBody;
}

void CollidableObject::setCollisionShape(std::shared_ptr<btCollisionShape> shape)
{
	m_collisionShape = shape;
}

void CollidableObject::setMotionState(std::shared_ptr<btDefaultMotionState> motionState)
{
	m_motionState = motionState;
}

CollidableObject::~CollidableObject()
{
	m_dynamicsWorld->removeRigidBody(m_rigidBody.get());
	btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
	m_dynamicsWorld->stepSimulation(deltaTime, 10); // Max 10 substeps for stability

}

