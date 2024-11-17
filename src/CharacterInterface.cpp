#include "CharacterInterface.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

const float CharacterInterface::GRAVITY = 9.8f; // Define GRAVITY

CharacterInterface::CharacterInterface(Model model, const Vector3& forwardDir, const Vector3& position, const Vector3& velocity,
                    const float& speed, const float& scale):
    m_position(position), 
    m_velocity(velocity),
    m_forwardDir(forwardDir),
    m_speed(speed), 
    m_isOnGround(true), 
    m_scale(scale),
    m_model(model)
{    // Compute the model's axis-aligned bounding box
    BoundingBox bbox = GetModelBoundingBox(m_model);

    // Calculate the center of the bounding box
    Vector3 center = { (bbox.min.x + bbox.max.x) / 2.0f,
                      (bbox.min.y + bbox.max.y) / 2.0f,
                      (bbox.min.z + bbox.max.z) / 2.0f };

    // Calculate the extents (half-dimensions of the bounding box)
    Vector3 extents = { (bbox.max.x - bbox.min.x) / 2.0f,
                       (bbox.max.y - bbox.min.y) / 2.0f,
                       (bbox.max.z - bbox.min.z) / 2.0f };

    // Scale the extents based on the model's scale factor
    extents = Vector3Scale(extents, m_scale);

    // Initialize the OBB
    m_bounds = OBB(center, extents);
}

void CharacterInterface::updateTransform() {
    // Translation matrix for position
    Matrix translationMatrix = MatrixTranslate(m_position.x, m_position.y, m_position.z);

    // Calculate the right vector as the cross product of the world up and forward direction
    Vector3 right = Vector3CrossProduct(Vector3{ 0.0f, 1.0f, 0.0f }, m_forwardDir);
    right = Vector3Normalize(right);

    // Calculate the up vector as the cross product of forward direction and right vector
    Vector3 up = Vector3CrossProduct(m_forwardDir, right);
    up = Vector3Normalize(up);

    // Create rotation matrix with right, up, and forward vectors as columns
    Matrix rotationMatrix = {
        right.x, up.x, m_forwardDir.x, 0.0f,
        right.y, up.y, m_forwardDir.y, 0.0f,
        right.z, up.z, m_forwardDir.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // Combine rotation and translation matrices (rotation first, then translation)
    m_model.transform = MatrixMultiply(rotationMatrix, translationMatrix);

    // Update the OBB with the new rotation matrix and position
    m_bounds.rotateAroundCenter(rotationMatrix, m_position);

    // Update the axes and extents of the OBB based on the transformed corners
    BoundingBox localBBox = GetModelBoundingBox(m_model);
    Vector3 corners[8] = {
        localBBox.min,
        {localBBox.max.x, localBBox.min.y, localBBox.min.z},
        {localBBox.min.x, localBBox.max.y, localBBox.min.z},
        {localBBox.min.x, localBBox.min.y, localBBox.max.z},
        {localBBox.max.x, localBBox.max.y, localBBox.min.z},
        {localBBox.max.x, localBBox.min.y, localBBox.max.z},
        {localBBox.min.x, localBBox.max.y, localBBox.max.z},
        localBBox.max
    };

    // Transform each corner using the model's full transform
    for (int i = 0; i < 8; i++) {
        corners[i] = Vector3Transform(corners[i], m_model.transform);
    }

    // Recompute the OBB based on transformed corners
    m_bounds.recomputeFromCorners(corners);
}




void CharacterInterface::update() {
    applyGravity();
    move();
	if (m_isOnGround)
        jump();
    rotate();
}

void CharacterInterface::render() {
    DrawModel(m_model, m_position, m_scale, RAYWHITE);
    
    /*BoundingBox bbox = m_bounds;

    Vector3 bboxCenter = Vector3Scale(Vector3Add(bbox.min, bbox.max), 0.5f);
    Vector3 bboxSize = Vector3Subtract(bbox.max, bbox.min);
    DrawCubeWires(bboxCenter, bboxSize.x, bboxSize.y, bboxSize.z, RED);*/
}

void CharacterInterface::setOnGround(bool isOnGround) {
    m_isOnGround = isOnGround;
}

OBB CharacterInterface::getBoundingBox() const {
    return m_bounds;
}

CharacterInterface::~CharacterInterface() {
    UnloadModel(m_model);
}
