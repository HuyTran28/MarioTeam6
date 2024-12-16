#pragma once

#include <raylib.h>
#include <string>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include "../CollidableObject.h"

class ItemData : public CollidableObject
{
private:
	Model m_model;
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_rotationAxis;
	float m_rotationAngle;
	std::string m_modelPath;
public:
	ItemData();
	ItemData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, Model& model, const Vector3& position, const Vector3& scale, const Vector3& rotaionAxis, float rotationAngle, const std::string& modelPath, std::shared_ptr<btDynamicsWorld> world);

	Model getModel() const;
	Vector3 getPosition() const;
	Vector3 getScale() const;
	Vector3 getRotationAxis() const;
	float getRotationAngle() const;
	std::string getModelPath() const;

	void setModel(Model& model);
	void setPosition(const Vector3& position);
	void setScale(const Vector3& scale);
	void setRotationAxis(const Vector3& rotationAxis);
	void setRotationAngle(float rotationAngle);
	void setModelPath(const std::string& modelPath);

	~ItemData();
};