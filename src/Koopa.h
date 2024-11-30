#include "Enemy.h"
#include "KoopaNormalState.h"

class Koopa : public PatrollingEnemy {
public:
    Koopa(btRigidBody* rigidBody, Model model, const Vector3& position, const Vector3& forwardDir, float speed, float scale, const Vector3& patrolPointA, const Vector3& patrolPointB, btDynamicsWorld* world);

    void move() override;

	void onCollision(const CollisionEvent& event) override;
    void changeToShellModel();
    void recalculatePhysicsForShell();
};