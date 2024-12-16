#pragma once

#include "../Model/CollidableObject.h"
#include "btBulletDynamicsCommon.h"
#include <vector>
#include "../Observer/IObserver.h"
#include "Event/EventManager.h"
#include <memory>
#include <mutex>

class CollisionManager : public IObserver, public std::enable_shared_from_this<CollisionManager>
{
private:
    std::shared_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
    std::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
    std::shared_ptr<btCollisionDispatcher> m_dispatcher;
    std::shared_ptr<btBroadphaseInterface> m_overlappingPairCache;
    std::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
    CollisionManager();
    void removeAllRigidBody();

    static std::shared_ptr<CollisionManager> instance;
    static std::mutex instanceMutex; // Add a mutex for thread safety

public:
    ~CollisionManager();
    static std::shared_ptr<CollisionManager> getInstance();
    CollisionManager(const CollisionManager& collisionManager) = delete;
    CollisionManager& operator=(const CollisionManager& collisionManager) = delete;
    void update(std::shared_ptr<Event> event) override;
    void detectCollisions();
    void handle(CollidableObject* obj1, CollidableObject* obj2, std::vector<btManifoldPoint> contactPoints);
    std::shared_ptr<btDiscreteDynamicsWorld> getDynamicsWorld() const;
};
