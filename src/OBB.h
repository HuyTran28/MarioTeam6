#pragma once
#include "raylib.h"

class OBB {
private:
    Vector3 m_center;
    Vector3 m_extents; 
    Vector3 m_axes[3];

public:
    OBB();
    OBB(const Vector3& center, const Vector3& extents);
	~OBB() = default;

    Vector3 getCenter() const;
    void setCenter(const Vector3& center);

    Vector3 getExtents() const;
    void setExtents(const Vector3& extents);

    void setAxes(const Vector3& right, const Vector3& up, const Vector3& forward);

    void recomputeFromCorners(const Vector3 corners[8]);

    void rotateAroundCenter(const Matrix& rotation, const Vector3& center);

    Vector3 getMin() const;
    Vector3 getMax() const;
    operator BoundingBox() const;
};