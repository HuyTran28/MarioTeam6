#include "BlockData.h"
#include <iostream>

BlockData::~BlockData()
{
    if (m_rigidBodyOfBlock && m_dynamicsWorld)
    {
        std::cout << "1\n";
        m_dynamicsWorld->removeRigidBody(m_rigidBodyOfBlock);
    }

    if(m_rigidBodyOfBlock)
        delete m_rigidBodyOfBlock;
    m_rigidBodyOfBlock = nullptr;

    auto it = std::find_if(
        ModelStage::listModels.begin(),
        ModelStage::listModels.end(),
        [this](const auto& pair) { return pair.second.meshes == m_model.meshes; });

    if (it == ModelStage::listModels.end()) {
        UnloadModel(m_model);
    }
}



btDiscreteDynamicsWorld* BlockData::getDynamicsWorld() const
{
    return m_dynamicsWorld;
}

btRigidBody* BlockData::getRigidBody() const
{
	return m_rigidBodyOfBlock;
}

std::string BlockData::getName() const
{
    return m_name;
}

Model BlockData::getModel() const
{
	return m_model;
}

Vector3 BlockData::getPosition() const
{
	return m_position;
}

Vector3 BlockData::getScale() const
{
	return m_scale;
}

Vector3 BlockData::getRotationAxis() const
{
    return m_rotationAxis;
}

float BlockData::getRotationAngle() const
{
    return m_rotationAngle;
}

bool BlockData::getIsBouncing() const
{
	return m_isBouncing;
}