#pragma once

#include <raylib.h>
#include <string>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include <fstream>

class CollidableObject
{
protected:
	std::shared_ptr<btDynamicsWorld> m_dynamicsWorld;
	std::shared_ptr<btRigidBody> m_rigidBody;
	std::shared_ptr<btCollisionShape> m_collisionShape;
	std::shared_ptr<btDefaultMotionState> m_motionState;
	std::string objectType;
	bool isCreatedRunTime = false;
public:
	CollidableObject();
	CollidableObject(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, std::shared_ptr<btDynamicsWorld> world);

	std::shared_ptr<btRigidBody> getRigidBody() const;
	std::shared_ptr<btCollisionShape> getCollisionShape() const;
	std::shared_ptr<btDefaultMotionState> getMotionState() const;
	std::shared_ptr<btDynamicsWorld> getDynamicsWorld() const;
	std::string getObjectType();
	void setObjectType(std::string type);
	bool getIsCreatedRunTime();
	void setIsCreatedRunTime(bool isCreatedRunTime);
	void setRigidBody(std::shared_ptr<btRigidBody> rigidBody);
	void setCollisionShape(std::shared_ptr<btCollisionShape> shape);
	void setMotionState(std::shared_ptr<btDefaultMotionState> motionState);

	virtual void save(std::ofstream& file);
	virtual void load(std::ifstream& file);

	virtual ~CollidableObject();
};