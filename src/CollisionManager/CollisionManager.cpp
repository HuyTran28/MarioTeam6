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

    for (int i = 0; i < m_dynamicsWorld->getDispatcher()->getNumManifolds(); ++i) {

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

bool CollisionManager::detectCollisionFromBelow(CollidableObject* obj1, CollidableObject* obj2)
{
    if (obj1->getRigidBody() && obj2->getRigidBody())
    {

        btTransform playerTransform;
        obj2->getMotionState()->getWorldTransform(playerTransform);
        btVector3 playerMin, playerMax;
        obj2->getCollisionShape()->getAabb(playerTransform, playerMin, playerMax);


        btTransform blockTransform;
        obj1->getRigidBody()->getMotionState()->getWorldTransform(blockTransform);
        btVector3 blockMin, blockMax;
        obj1->getRigidBody()->getCollisionShape()->getAabb(blockTransform, blockMin, blockMax);



        bool isOverlappingX = (playerMax.x() >= blockMin.x()) && (playerMin.x() <= blockMax.x());
        bool isOverlappingY = (blockMin.y() - playerMax.y() < 0.1) && (blockMin.y() - playerMax.y() >= 0.0f);
        bool isOverlappingZ = (playerMax.z() >= blockMin.z()) && (playerMin.z() <= blockMax.z());


        return isOverlappingX && isOverlappingY && isOverlappingZ;
    }
}

bool CollisionManager::detectCollisionFromAbove(CollidableObject* obj1, CollidableObject* obj2)
{
    if (!obj2->getRigidBody() || !obj1->getRigidBody()) return false;

    btTransform playerTransform, blockTransform;
    obj2->getRigidBody()->getMotionState()->getWorldTransform(playerTransform);
    obj1->getRigidBody()->getMotionState()->getWorldTransform(blockTransform);

    btVector3 playerMin, playerMax;
    obj2->getRigidBody()->getCollisionShape()->getAabb(playerTransform, playerMin, playerMax);

    // Raycasting from playerMin slightly below the player
    btVector3 rayStart = playerMin + btVector3(0, -0.1f, 0);
    btVector3 rayEnd = rayStart - btVector3(0.0f, 1.0f, 0.0f);


    btCollisionWorld::ClosestRayResultCallback rayCallback(rayStart, rayEnd);
    m_dynamicsWorld->rayTest(rayStart, rayEnd, rayCallback);

    if (rayCallback.hasHit()) {
        const btCollisionObject* hitObject = rayCallback.m_collisionObject;
        return hitObject == obj2->getRigidBody().get(); // True if the ray hits this block
    }
}






void CollisionManager::handle(CollidableObject* obj1, CollidableObject* obj2, std::vector<btManifoldPoint> contactPoints)
{
    // Handle collision
    if (contactPoints.size() <=0 ) return;

    std::string objectType1 = obj1->getObjectType();
    std::string objectType2 = obj2->getObjectType();

    if (objectType1 > objectType2)
		handle(obj2, obj1, contactPoints);

    //if (objectType1 == "Block-NormalBrickBlock" && objectType2 == "Player-Normal")  
    //{
    //    
    //    BlockData* blockData = dynamic_cast<BlockData*>(obj1);
    //     if (detectCollisionFromBelow(contactPoints))
    //     {
    //        blockData->setIsBounce(true);
    //        blockData->setBouncetime(TILE_DURATION);
    //    }
    //}

    if (objectType1 == "Block-Question" && objectType2 == "Player-Normal")
    {
       
        if (detectCollisionFromBelow(obj1,  obj2))
        {
            BlockData* block = dynamic_cast<BlockData*>(obj1);
            std::shared_ptr<BlockData> newBlock = BlockFactory::createBlock(BlockType::EmptyBlock, CollisionManager::getInstance()->getDynamicsWorld(),
                "../../Assets\\Models\\Platforms\\EmptyBlock.glb",
                block->getPosition(), block->getScale(),
                block->getRotationAxis(), block->getRotationAngle());

            EventManager::getInstance().notify(std::make_shared<BlockChangeEvent>(block, newBlock));
         
        }
    }

    if (objectType1 == "Block-Pipe" && objectType2 == "Player-Normal")
    {
        PipeBlock* block = dynamic_cast<PipeBlock*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);

        if (IsKeyPressed(KEY_S) && detectCollisionFromAbove(obj1, obj2))
        {
     
            player->getRigidBody().get()->translate(block->getNewPosition());
        }

    }

}
