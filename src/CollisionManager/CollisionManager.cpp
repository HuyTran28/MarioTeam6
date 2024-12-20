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

bool CollisionManager::detectCollisionFromBelow(std::vector<btManifoldPoint> contactPoints)
{

    bool collisionFromBelow = false;

    // Loop through all contact points
    for (const btManifoldPoint& cp : contactPoints) {
        // Get the contact normal in world coordinates
        btVector3 normalOnTarget = cp.m_normalWorldOnB;

        // Check if the normal is pointing upwards (i.e., collision from below)
        if (normalOnTarget.y() == 1) { // Adjust threshold if necessary
            collisionFromBelow = true;
            break;  // Exit loop early if collision from below is detected
        }
    }

    return collisionFromBelow;
}

bool CollisionManager::detectCollisionFromAbove(std::vector<btManifoldPoint> contactPoints)
{

    bool collisionFromAbove = false;

    // Loop through all contact points
    for (const btManifoldPoint& cp : contactPoints) {
        // Get the contact normal in world coordinates
        btVector3 normalOnTarget = cp.m_normalWorldOnB;

        // Check if the normal is pointing upwards (i.e., collision from below)
        if (normalOnTarget.y() == - 1) { // Adjust threshold if necessary
            collisionFromAbove = true;
            break;  // Exit loop early if collision from below is detected
        }
    }

    return collisionFromAbove;
}

bool CollisionManager::detectCollisionFromAboveEnemy(std::vector<btManifoldPoint> contactPoints)
{

    bool collisionFromAbove = false;

    // Loop through all contact points
    for (const btManifoldPoint& cp : contactPoints) {
        // Get the contact normal in world coordinates
        btVector3 normalOnTarget = cp.m_normalWorldOnB;

        // Check if the normal is pointing upwards (i.e., collision from below)
        if (normalOnTarget.y() < -0.6) { // Adjust threshold if necessary
            collisionFromAbove = true;
            break;  // Exit loop early if collision from below is detected
        }
    }

    return collisionFromAbove;
}

bool CollisionManager::detectCollisionFromLeft(std::vector<btManifoldPoint> contactPoints)
{

    bool collisionFromLeft = false;

    // Loop through all contact points
    for (const btManifoldPoint& cp : contactPoints) {
        // Get the contact normal in world coordinates
        btVector3 normalOnTarget = cp.m_normalWorldOnB;

        // Check if the normal is pointing upwards (i.e., collision from below)
        if (normalOnTarget.x() == 1) { // Adjust threshold if necessary
            collisionFromLeft = true;
            break;  // Exit loop early if collision from below is detected
        }
    }

    return collisionFromLeft;
}


void CollisionManager::handle(CollidableObject* obj1, CollidableObject* obj2, std::vector<btManifoldPoint> contactPoints)
{
    // Handle collision
    if (contactPoints.size() <=0 ) return;

    std::string objectType1 = obj1->getObjectType();
    std::string objectType2 = obj2->getObjectType();

    if (objectType1 > objectType2)
    {
        handle(obj2, obj1, contactPoints);
        return;
    }

    if (objectType1 == "Block-NormalBrickBlock" && objectType2.substr(0, 6) == "Player")
    {
            
            BlockData* blockData = dynamic_cast<BlockData*>(obj1);

            if (detectCollisionFromBelow(contactPoints))
            {
                blockData->setIsBounce(true);
                blockData->setBouncetime(TILE_DURATION);
            }  
    }

    if (objectType1 == "Block-Question" && objectType2.substr(0, 6) == "Player")
    {
       
        if (detectCollisionFromBelow(contactPoints))
        {
            BlockData* block = dynamic_cast<BlockData*>(obj1);
            std::shared_ptr<BlockData> newBlock = BlockFactory::createBlock(BlockType::EmptyBlock, CollisionManager::getInstance()->getDynamicsWorld(),
                "../../Assets\\Models\\Platforms\\EmptyBlock.glb",
                block->getPosition(), block->getScale(),
                block->getRotationAxis(), block->getRotationAngle());

            EventManager::getInstance().notify(std::make_shared<BlockChangeEvent>(block, newBlock));
         
        }
    }

    if (objectType1 == "Block-Pipe" && objectType2.substr(0, 6) == "Player")
    {
        PipeBlock* block = dynamic_cast<PipeBlock*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);

        if (IsKeyPressed(KEY_S) && detectCollisionFromAbove(contactPoints))
        {
			EventManager::getInstance().notify(std::make_shared<WarpEvent>());
            player->getRigidBody().get()->translate(block->getNewPosition());
        }

    }

    if (objectType1 == "Block-UpPipe" && objectType2.substr(0, 6) == "Player")
    {
        SupportivePipeBLock* block = dynamic_cast<SupportivePipeBLock*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        if (detectCollisionFromLeft(contactPoints))
        {
            player->getRigidBody().get()->translate(block->getNewPosition());
        }
    }

    if (objectType1 == "Item-Coin" && objectType2.substr(0, 6) == "Player")
    {
		Coin* coin = dynamic_cast<Coin*>(obj1);
		PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(coin));
    }

    if (objectType1 == "Block-NormalBrickBlock" && objectType2 == "Player-Big")
    {
        if (detectCollisionFromBelow(contactPoints))
        {
            BlockData* block = dynamic_cast<BlockData*>(obj1);
            std::shared_ptr<BlockData> newBlock = nullptr;

            EventManager::getInstance().notify(std::make_shared<BlockChangeEvent>(block, newBlock));
        }
    }
   
    if (objectType1 == "Item-RedMushroom" && objectType2 == "Player-Normal")
    {
        RedMushroom* redMushroom = dynamic_cast<RedMushroom*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(redMushroom));
        player->setBigDuration(30.0f);
        player->setIsBig(true);
        player->setPlayerScale(Vector3Multiply(player->getPlayerScale(), Vector3{ 1.25f, 1.25f, 1.25f }));
        player->setObjectType("Player-Big");
    }

    if ((objectType1 == "Item-PurpleMushroom" && objectType2 == "Player-Normal"))
    {
        PurpleMushroom* purpleMushroom = dynamic_cast<PurpleMushroom*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(purpleMushroom));

        player->setPlayerHealth(0);
    }

    if ((objectType1 == "Item-PurpleMushroom" && objectType2 == "Player-Big"))
    {
        PurpleMushroom* purpleMushroom = dynamic_cast<PurpleMushroom*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(purpleMushroom));
   
        player->setPlayerScale(Vector3Multiply(player->getPlayerScale(), Vector3{ 1.0 /1.25f, 1.0 / 1.25f, 1.0 /1.25f }));
    }

	if (objectType1 == "Item-GreenMushroom" && objectType2.substr(0, 6) == "Player")
	{
		GreenMushroom* greenMushroom = dynamic_cast<GreenMushroom*>(obj1);
		PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(greenMushroom));

		EventManager::getInstance().notify(std::make_shared<RegenerateEvent>());
		player->setPlayerHealth(player->getPlayerHealth() + 1);

	}

	if ((objectType1 == "Enemy-Goomba" && objectType2 == "Player-Normal") || (objectType1 == "Enemy-Goomba" && objectType2 == "Player-Big"))
	{
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		Goomba* goomba = dynamic_cast<Goomba*>(obj1);

        if (detectCollisionFromAboveEnemy(contactPoints))
        {
			EventManager::getInstance().notify(std::make_shared<EnemyDie>(goomba));
            return;
        }

        if (!player->getIsvincible() && player->getIsOnGround())
        {
            player->setPlayerHealth(player->getPlayerHealth() - 1);


            if (player->getPlayerHealth() > 0) {
                player->setIsvincible(true);
          
                player->setInvincibilityTimer(player->getInvincibilityDuration());
                player->setPlayerAnimationState(PlayerAnimationState::HIT); // Trigger hit animation
            }
        }


       
	}
}
