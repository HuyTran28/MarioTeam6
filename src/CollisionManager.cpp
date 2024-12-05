#include "CollisionManager.h"
#include "Enemy.h"
#include "Player.h"

CollisionManager::CollisionManager(btDynamicsWorld* world): dynamicsWorld(world) {}

void CollisionManager::detectCollisions() {
    dynamicsWorld->performDiscreteCollisionDetection();

    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
 
    for (int i = 0; i < numManifolds; ++i) {
        btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);

        btRigidBody* body0 = const_cast<btRigidBody*>(static_cast<const btRigidBody*>(contactManifold->getBody0()));
        btRigidBody* body1 = const_cast<btRigidBody*>(static_cast<const btRigidBody*>(contactManifold->getBody1()));

        CharacterInterface* obj1 = static_cast<CharacterInterface*>(body0->getUserPointer());
        CharacterInterface* obj2 = static_cast<CharacterInterface*>(body1->getUserPointer());

        // Delegate to objects to determine type
        if (!obj1 || !obj2) continue;

        // Create a collision event
        CollisionEvent event = { obj1, obj2, {}, CollisionType::Idle, {0, 0, 0} };

        // Collect contact points
        for (int j = 0; j < contactManifold->getNumContacts(); ++j) {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            event.contactPoints.push_back(pt);
        }

        obj1->determineCollisionType(event);
        obj2->determineCollisionType(event);

        // Dispatch event
        dispatch(event);
    }
}



void CollisionManager::dispatch(const CollisionEvent& event) {
    event.obj1->onCollision(event);
    event.obj2->onCollision(event);
}
