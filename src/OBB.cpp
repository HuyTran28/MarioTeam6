#include "OBB.h"
#include "OBB.h"
#include "raymath.h"

OBB::OBB() : m_center{0.0f, 0.0f, 0.0f}, m_extents{1.0f, 1.0f, 1.0f}, m_axes{Vector3{1.0f, 0.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}, Vector3{0.0f, 0.0f, 1.0f}} {}

OBB::OBB(const Vector3& center, const Vector3& extents)
    : m_center(center), m_extents(extents), m_axes{Vector3{1.0f, 0.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}, Vector3{0.0f, 0.0f, 1.0f}}
{}

Vector3 OBB::getCenter() const {
    return m_center;
}

void OBB::setCenter(const Vector3& center) {
    m_center = center;
}

Vector3 OBB::getExtents() const {
    return m_extents;
}

void OBB::setExtents(const Vector3& extents) {
    m_extents = extents;
}

Vector3 OBB::getMin() const {
    return Vector3Subtract(m_center, m_extents);
}

Vector3 OBB::getMax() const {
    return Vector3Add(m_center, m_extents);
}

OBB::operator BoundingBox() const {
    return { getMin(), getMax() };
}

void OBB::setAxes(const Vector3& right, const Vector3& up, const Vector3& forward) {
    m_axes[0] = Vector3Normalize(right);
    m_axes[1] = Vector3Normalize(up);
    m_axes[2] = Vector3Normalize(forward);
}

void OBB::recomputeFromCorners(const Vector3 corners[8]) {
    // Recompute center as the average of all corners
    m_center = { 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 8; i++) {
        m_center = Vector3Add(m_center, corners[i]);
    }
    m_center = Vector3Scale(m_center, 1.0f / 8.0f);

    // Use the edges to compute axes
    Vector3 edge1 = Vector3Subtract(corners[1], corners[0]); // Right vector
    Vector3 edge2 = Vector3Subtract(corners[2], corners[0]); // Up vector
    Vector3 edge3 = Vector3Subtract(corners[4], corners[0]); // Forward vector

    m_axes[0] = Vector3Normalize(edge1);
    m_axes[1] = Vector3Normalize(edge2);
    m_axes[2] = Vector3Normalize(edge3);

    // Compute extents as half the length of each axis
    m_extents = {
        Vector3Length(edge1) * 0.5f,
        Vector3Length(edge2) * 0.5f,
        Vector3Length(edge3) * 0.5f
    };
}

void OBB::rotateAroundCenter(const Matrix& rotation, const Vector3& center) {
    // Update axes by applying the rotation matrix
    for (int i = 0; i < 3; i++) {
        m_axes[i] = Vector3Transform(m_axes[i], rotation);
        m_axes[i] = Vector3Normalize(m_axes[i]); // Normalize to ensure orthogonality
    }

    // Update the center by rotating it around the given point
    Vector3 translationToOrigin = Vector3Subtract(m_center, center);
    Vector3 rotatedTranslation = Vector3Transform(translationToOrigin, rotation);
    m_center = Vector3Add(rotatedTranslation, center);
}


//void OBB::rotateAroundCenter(const Matrix& rotation, const Vector3& center) {
//	// Translate the center to the origin
//	Vector3 localCenter = Vector3Subtract(m_center, center);
//
//	// Rotate the center
//	localCenter = Vector3Transform(localCenter, rotation);
//
//	// Translate the center back
//	m_center = Vector3Add(localCenter, center);
//
//	// Rotate the axes
//	for (int i = 0; i < 3; i++) {
//		m_axes[i] = Vector3Transform(m_axes[i], rotation);
//	}
//}