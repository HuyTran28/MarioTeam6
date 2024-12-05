#include "CollisionUtils.h"
#include "Player.h"
#include "Enemy.h"

namespace CollisionUtils {

    bool isContactPointNearCapsuleEnd(const std::vector<btManifoldPoint>& contactPoints, const btVector3& capsuleCenter, float capsuleRadius, float capsuleHeight, bool checkTop, const btVector3& velocity) {
        const float epsilon = 0.01f;

        // Ensure the object is moving downward if we're checking for a stomp
        bool isMovingDown = velocity.getY() < -0.1f;  // Negative Y velocity indicates downward movement

        for (const auto& contactPoint : contactPoints) {
            btVector3 position = contactPoint.getPositionWorldOnB();

            float distanceToEnd = checkTop
                ? position.getY() - (capsuleCenter.getY() + capsuleHeight / 2.0f)
                : (capsuleCenter.getY() - capsuleHeight / 2.0f) - position.getY();

            if (abs(distanceToEnd) <= capsuleRadius + epsilon && isMovingDown) {
                return true;
            }
        }
        return false;
    }

    void determineCollisionType(CollisionEvent& event) {
        CharacterInterface* obj1 = event.obj1;
        CharacterInterface* obj2 = event.obj2;

        btRigidBody* body1 = obj1->getRigidBody();
        btRigidBody* body2 = obj2->getRigidBody();

        // Retrieve the capsule's center, radius, and height
        btCapsuleShape* capsuleShape1 = static_cast<btCapsuleShape*>(body1->getCollisionShape());
        btCapsuleShape* capsuleShape2 = static_cast<btCapsuleShape*>(body2->getCollisionShape());

        if (!capsuleShape1 || !capsuleShape2) {
            // If not capsule shapes, handle differently or return
            return;
        }

        btVector3 capsuleCenter1 = body1->getWorldTransform().getOrigin();
        btVector3 capsuleCenter2 = body2->getWorldTransform().getOrigin();

        float capsuleRadius1 = capsuleShape1->getRadius();
        float capsuleHeight1 = capsuleShape1->getHalfHeight() * 2.0f;
        float capsuleRadius2 = capsuleShape2->getRadius();
        float capsuleHeight2 = capsuleShape2->getHalfHeight() * 2.0f;

        btVector3 velocity1 = body1->getLinearVelocity();
        btVector3 velocity2 = body2->getLinearVelocity();

        bool isLowestPoint = isContactPointNearCapsuleEnd(event.contactPoints, capsuleCenter1, capsuleRadius1, capsuleHeight1, false, velocity1);
        bool isHighestPoint = isContactPointNearCapsuleEnd(event.contactPoints, capsuleCenter2, capsuleRadius2, capsuleHeight2, true, velocity2);

        const float KICK_SPEED_THRESHOLD = 5.0f;
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

