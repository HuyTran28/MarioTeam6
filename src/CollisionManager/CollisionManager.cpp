#include "CollisionManager.h"
#include <mutex>
#include <iostream>

std::shared_ptr<CollisionManager> CollisionManager::instance = nullptr;
std::mutex CollisionManager::instanceMutex;

CollisionManager::CollisionManager()
{
    m_collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
    m_dispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfiguration.get());
    m_overlappingPairCache = std::make_shared<btDbvtBroadphase>();
    m_solver = std::make_shared<btSequentialImpulseConstraintSolver>();
    m_dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());

    m_dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}

void CollisionManager::removeAllRigidBody()
{
 //   // Get the number of collision objects
 //   int numObjects = m_dynamicsWorld->getNumCollisionObjects();

	//std::cout << numObjects << std::endl;

 //   // Iterate backward to safely remove all rigid bodies
 //   for (int i = numObjects - 1; i >= 0; i--) {
 //       btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
 //       


 //       // Cast to btRigidBody (optional, if you only care about rigid bodies)
 //       btRigidBody* body = btRigidBody::upcast(obj);

 //       if (obj == nullptr)
 //           continue;

 //       if (body != nullptr) {
 //           // Remove the rigid body from the world
 //           m_dynamicsWorld->removeRigidBody(body);
 //       }
 //       else {
 //           // If not a rigid body, remove the collision object
 //           m_dynamicsWorld->removeCollisionObject(obj);
 //       }
   
}


CollisionManager::~CollisionManager()
{
	removeAllRigidBody();
}

std::shared_ptr<btDiscreteDynamicsWorld> CollisionManager::getDynamicsWorld() const
{
    return m_dynamicsWorld;
}

std::shared_ptr<CollisionManager> CollisionManager::getInstance()
{
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance) {
        instance = std::shared_ptr<CollisionManager>(new CollisionManager());
		EventManager::getInstance().addObserver(instance);
    }
    return instance;
}

void CollisionManager::update(std::shared_ptr<Event> event)
{
    if (event->getType() == "Tick Event") {
        m_dynamicsWorld->stepSimulation(GetFrameTime());
        detectCollisions();
    }
}

void CollisionManager::detectCollisions()
{
    m_dynamicsWorld->performDiscreteCollisionDetection();
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; ++i) {
        btPersistentManifold* contactManifold = m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btRigidBody* body0 = const_cast<btRigidBody*>(static_cast<const btRigidBody*>(contactManifold->getBody0()));
        btRigidBody* body1 = const_cast<btRigidBody*>(static_cast<const btRigidBody*>(contactManifold->getBody1()));
        CollidableObject* obj1 = static_cast<CollidableObject*>(body0->getUserPointer());
        CollidableObject* obj2 = static_cast<CollidableObject*>(body1->getUserPointer());
        if (!obj1 || !obj2) continue;
        std::vector<btManifoldPoint> contactPoints;
        for (int j = 0; j < contactManifold->getNumContacts(); ++j) {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            contactPoints.push_back(pt);
        }
        handle(obj1, obj2, contactPoints);
    }
}

void CollisionManager::handle(CollidableObject* obj1, CollidableObject* obj2, std::vector<btManifoldPoint> contactPoints)
{
    // Handle collision
    std::string objectType1 = obj1->getObjectType();
    std::string objectType2 = obj2->getObjectType();

    if (objectType1 > objectType2)
		handle(obj2, obj1, contactPoints);

    if (true) {
        // Collision handling logic
    }
}
