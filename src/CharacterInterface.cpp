#include "CharacterInterface.h"

const float CharacterInterface::GRAVITY = 9.8f;

CharacterInterface::CharacterInterface(btRigidBody* rigidBody, Model model, const Vector3& forwardDir, const Vector3& position,
    const float& speed, const float& scale)
    : m_rigidBody(rigidBody), m_model(model), m_position(position), m_forwardDir(forwardDir), m_speed(speed), m_scale(scale), m_isOnGround(true) {}
