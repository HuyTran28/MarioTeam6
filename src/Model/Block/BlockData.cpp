#include "BlockData.h"
#include <iostream>

BlockData::~BlockData()
{
    auto it = std::find_if(
        ModelStage::listModels.begin(),
        ModelStage::listModels.end(),
        [this](const auto& pair) { return pair.second.meshes == m_model.meshes; });

    if (it == ModelStage::listModels.end()) {
        UnloadModel(m_model);
    }
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