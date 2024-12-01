#include "CollisionUtils.h"
#include "Player.h"
#include "Enemy.h"

namespace CollisionUtils {

    bool isContactPointAtBoundingBoxEdge(const std::vector<btManifoldPoint>& contactPoints, const btVector3& min, const btVector3& max, bool checkTop) {
        const float epsilon = 0.01f;
        for (const auto& contactPoint : contactPoints) {
            btVector3 normal = contactPoint.m_normalWorldOnB;
            if (checkTop) {
                if (normal.getY() > 0.9f && contactPoint.getPositionWorldOnB().getY() >= max.getY() - epsilon) {
                    return true;
                }
            }
            else {
                if (normal.getY() > 0.9f && contactPoint.getPositionWorldOnA().getY() <= min.getY() + epsilon) {
                    return true;
                }
            }
        }
        return false;
    }

    void determineCollisionType(CollisionEvent& event) {
        CharacterInterface* obj1 = event.obj1;
        CharacterInterface* obj2 = event.obj2;

        btRigidBody* body1 = obj1->getRigidBody();
        btRigidBody* body2 = obj2->getRigidBody();

        btVector3 min1, max1, min2, max2;
        body1->getCollisionShape()->getAabb(body1->getWorldTransform(), min1, max1);
        body2->getCollisionShape()->getAabb(body2->getWorldTransform(), min2, max2);

        bool isLowestPoint = isContactPointAtBoundingBoxEdge(event.contactPoints, min1, max1, false);
        bool isHighestPoint = isContactPointAtBoundingBoxEdge(event.contactPoints, min2, max2, true);

        const float KICK_SPEED_THRESHOLD = 5.0f;
        btVector3 velocity1 = body1->getLinearVelocity();
        btVector3 velocity2 = body2->getLinearVelocity();
        btVector3 relativeVelocity = velocity1 - velocity2;

        bool isKicking = relativeVelocity.length() > KICK_SPEED_THRESHOLD;

        if (isLowestPoint) {
            event.type = CollisionType::Stomped;
        }
        else if (isKicking) {
            event.type = CollisionType::Kicked;
            event.kickDirection = relativeVelocity.normalized();
        }
        else {
            event.type = CollisionType::HitByEnemy;
        }
    }


} // namespace CollisionUtils
