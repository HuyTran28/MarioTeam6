#pragma once
#include <vector>
#include "btBulletDynamicsCommon.h"
#include "CollisionEvent.h"

namespace CollisionUtils {

	bool isContactPointAtBoundingBoxEdge(const std::vector<btManifoldPoint>& contactPoints, const btVector3& min, const btVector3& max, bool checkTop);

	void determineCollisionType(CollisionEvent& event);

} // namespace CollisionUtils
