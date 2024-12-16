#include "ItemData.h"

ItemData::ItemData()
{
	m_modelPath = "../../Assets\\Models\\joystick2.glb";
	m_model = LoadModel(m_modelPath.c_str());
	m_position = Vector3{ 0.0f, 0.0f, 0.0f };
	m_scale = Vector3{ 10.0f, 10.0f, 10.0f };
	m_rotationAxis = Vector3{ 0.0f, 1.0f, 0.0f };
	m_rotationAngle = 0.0f;
}

ItemData::ItemData(std::shared_ptr<btRigidBody> rigidBody, std::shared_ptr<btCollisionShape> shape, std::shared_ptr<btDefaultMotionState> motionState, Model& model, const Vector3& position, const Vector3& scale, const Vector3& rotaionAxis, float rotationAngle, const std::string& modelPath, std::shared_ptr<btDynamicsWorld> world)
	: CollidableObject(rigidBody, shape, motionState, world), m_model(model), m_position(position), m_scale(scale), m_rotationAxis(rotaionAxis), m_rotationAngle(rotationAngle), m_modelPath(modelPath)
{
}

Model ItemData::getModel() const
{
	return m_model;
}

Vector3 ItemData::getPosition() const
{
	return m_position;
}

Vector3 ItemData::getScale() const
{
	return m_scale;
}

Vector3 ItemData::getRotationAxis() const
{
	return m_rotationAxis;
}

float ItemData::getRotationAngle() const
{
	return m_rotationAngle;
}

std::string ItemData::getModelPath() const
{
	return m_modelPath;
}

void ItemData::setModel(Model& model)
{
	m_model = model;
}

void ItemData::setPosition(const Vector3& position)
{
	m_position = position;
}

void ItemData::setScale(const Vector3& scale)
{
	m_scale = scale;
}

void ItemData::setRotationAxis(const Vector3& rotationAxis)
{
	m_rotationAxis = rotationAxis;
}

void ItemData::setRotationAngle(float rotationAngle)
{
	m_rotationAngle = rotationAngle;
}

void ItemData::setModelPath(const std::string& modelPath)
{
	m_modelPath = modelPath;
}

ItemData::~ItemData()
{
	UnloadModel(m_model);
}

