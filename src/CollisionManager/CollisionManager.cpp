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
        std::cout << obj1->getObjectType() << " " << obj2->getObjectType() << '\n';
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
        if (normalOnTarget.y() < -0.6 || normalOnTarget.y() > 0.6 ) { // Adjust threshold if necessary
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

bool CollisionManager::detectCollisionFromRight(std::vector<btManifoldPoint> contactPoints)
{
    bool collisionFromRight = false;

    // Loop through all contact points
    for (const btManifoldPoint& cp : contactPoints) {
        // Get the contact normal in world coordinates
        btVector3 normalOnTarget = cp.m_normalWorldOnB;

        // Check if the normal is pointing upwards (i.e., collision from below)
        if (normalOnTarget.x() == -1) { // Adjust threshold if necessary
            collisionFromRight = true;
            break;  // Exit loop early if collision from below is detected
        }
    }

    return collisionFromRight;
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

            if (detectCollisionFromBelow(contactPoints) && obj1->getIsCreatedRunTime() == false)
            {
                blockData->setIsBounce(true);
                blockData->setBouncetime(TILE_DURATION);
            }  
			if (detectCollisionFromAbove(contactPoints) && obj1->getIsCreatedRunTime() == true)
			{
				blockData->setIsBounce(true);
				blockData->setBouncetime(TILE_DURATION);
			}
    }

    if (objectType1 == "Block-Question" && objectType2.substr(0, 6) == "Player")
    {
        BlockData* block = dynamic_cast<BlockData*>(obj1);
        if (detectCollisionFromAbove(contactPoints) || detectCollisionFromBelow(contactPoints))
        {
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

        if (IsKeyPressed(KEY_S) && (detectCollisionFromAbove(contactPoints) || detectCollisionFromBelow(contactPoints)))
        {
			EventManager::getInstance().notify(std::make_shared<WarpEvent>());
            player->getRigidBody().get()->translate(block->getNewPosition());
        }

    }

    if (objectType1 == "Block-UpPipe" && objectType2.substr(0, 6) == "Player")
    {
        SupportivePipeBLock* block = dynamic_cast<SupportivePipeBLock*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        if (detectCollisionFromLeft(contactPoints) || detectCollisionFromRight(contactPoints))
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
        if (detectCollisionFromBelow(contactPoints) || detectCollisionFromAbove(contactPoints))
        {
            BlockData* block = dynamic_cast<BlockData*>(obj1);
            std::shared_ptr<BlockData> newBlock = nullptr;

            EventManager::getInstance().notify(std::make_shared<BlockChangeEvent>(block, newBlock));
        }
    }
   
    if (objectType1 == "Item-RedMushroom" && objectType2.substr(0, 6) == "Player")
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
   
		player->setBigDuration(0.1f);
		player->setIsBig(true);
    }

    if (objectType1 == "Item-BoomerangFlower" && objectType2.substr(0,6) == "Player")
    {
        BoomerangFlower* flower = dynamic_cast<BoomerangFlower*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(flower));

        player->setIsUsed(true);
        player->setTimeOfBoomerang(player->getDurationBoomerang());

    }

    if (objectType1 == "Enemy-Goomba" && objectType2 == "Item-Boomerang")
    {
        Goomba* goomba = dynamic_cast<Goomba*>(obj1);
        goomba->setIsDie(true);
        Boomerang* boomerang = dynamic_cast<Boomerang*>(obj2);
        EventManager::getInstance().notify(std::make_shared<EnemyDie>(goomba));
    }

    if (objectType1 == "Enemy-Koopa" && objectType2 == "Item-Boomerang")
    {
        Koopa* koopa = dynamic_cast<Koopa*>(obj1);
        Boomerang* boomerang = dynamic_cast<Boomerang*>(obj2);
        EventManager::getInstance().notify(std::make_shared<EnemyDie>(koopa));
    }

    if (objectType1 == "Enemy-Bowser" && objectType2 == "Item-Boomerang")
    {
        Bowser* bowser = dynamic_cast<Bowser*>(obj1);
        Boomerang* boomerang = dynamic_cast<Boomerang*>(obj2);
		bowser->setPlayerHealth(bowser->getPlayerHealth() - 1);
    }

    if (objectType1 == "Item-Boomerang" && objectType2.substr(0, 6) == "Player")
    {
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        Boomerang* boomerang = dynamic_cast<Boomerang*>(obj1);
        if (boomerang->getIsreturning())
        {
            boomerang->setIsVisble(false);
            boomerang->setIsreturning(false);
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0.0f, -20.0f, 0.0f));
            boomerang->setRigidBodyTransform(transform);
            boomerang->setTravelDis(0.0f);
        }
    }

    if (objectType1 == "Enemy-Bowser" && objectType2 == "Item-Fire")
    {
        Bowser* bowser = dynamic_cast<Bowser*>(obj1);
        Fire* fire = dynamic_cast<Fire*>(obj2);
        if (fire->getIsreturning())
        {
            fire->setIsVisble(false);
            fire->setIsreturning(false);
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0.0f, -50.0f, 0.0f));
            fire->setRigidBodyTransform(transform);
            fire->setTravelDis(0.0f);
        }
    }


    if (objectType1 == "Item-Boomerang" || objectType2 == "Item-Boomerang")
    {
        std::cout << objectType1 << " " << objectType2 << std::endl;
    }

    if (objectType1.substr(0, 5) == "Block" && objectType2 == "Item-Boomerang")
    {
        Boomerang* boomerang = dynamic_cast<Boomerang*>(obj2);
        if (boomerang->getIsreturning())
        {
            boomerang->setIsVisble(false);
            boomerang->setIsreturning(false);
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0.0f, -20.0f, 0.0f));
            boomerang->setRigidBodyTransform(transform);
            boomerang->setTravelDis(0.0f);
        }
		else {
			boomerang->setIsreturning(true);
		}
    }

	if (objectType1 == "Item-GreenMushroom" && objectType2.substr(0, 6) == "Player")
	{
		GreenMushroom* greenMushroom = dynamic_cast<GreenMushroom*>(obj1);
		PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(greenMushroom));

		EventManager::getInstance().notify(std::make_shared<RegenerateEvent>());
		player->setPlayerHealth(player->getPlayerHealth() + 1);
	}

    if (objectType1 == "Item-SuperStar" && objectType2.substr(0, 6) == "Player")
    {
        SuperStar* superStar = dynamic_cast<SuperStar*>(obj1);
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        EventManager::getInstance().notify(std::make_shared<ItemTouchedEvent>(superStar));
        player->setMoveSpeed(player->getMoveSpeed() * 2.0f);
        player->setIsSpecial(true);
        player->setSpecialTimer(player->getSpecialDuration());
        player->setObjectType("Player-Special");
    }

    
   
	if ((objectType1 == "Enemy-Goomba" && objectType2.substr(0, 6) == "Player"))
	{
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		Goomba* goomba = dynamic_cast<Goomba*>(obj1);

        if (objectType2 == "Player-Special")
        {
            EventManager::getInstance().notify(std::make_shared<EnemyDie>(goomba));
            goomba->setIsDie(true);
            return;
        }

        if (detectCollisionFromAboveEnemy(contactPoints))
        {
			EventManager::getInstance().notify(std::make_shared<EnemyDie>(goomba));
            goomba->setIsDie(true);
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

    if ((objectType1 == "Enemy-Bowser" && objectType2.substr(0, 6) == "Player"))
    {
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        Bowser* bowser = dynamic_cast<Bowser*>(obj1);

        if (objectType2 == "Player-Special")
        {
			bowser->setPlayerHealth(bowser->getPlayerHealth() - 1);
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

    if ((objectType1 == "Enemy-Koopa" && objectType2.substr(0, 6) == "Player"))
    {
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
        Koopa* koopa = dynamic_cast<Koopa*>(obj1);

        if (detectCollisionFromAboveEnemy(contactPoints))
        {
            if (koopa->getState() == "Normal")
            {
				std::shared_ptr<Koopa> newKoopa = std::dynamic_pointer_cast<Koopa>(EnemyFactory::createEnemy(EnemyType::Koopa, CollisionManager::getInstance()->getDynamicsWorld(),
					"../../Assets\\Models\\Characters\\KoopaShell.glb",
					koopa->getPlayerPos(), koopa->getForwardDir(), koopa->getPlayerRotationAxis(), koopa->getPlayerRotationAngle(), koopa->getPlayerScale(), 10.0f, koopa->getPlayerPos(), koopa->getPlayerPos()) );
                EventManager::getInstance().notify(std::make_shared<EnemyChangeEvent>(koopa, newKoopa));
				
				newKoopa->Enemy::setState(EnemyState::SHELL);
            }
            return;
        }

        if (!player->getIsvincible() && player->getIsOnGround())
        {
            if (koopa->Enemy::getState() == EnemyState::SHELL)
			{
                btRigidBody* koopaBody = koopa->getRigidBody().get();
                koopaBody->applyCentralForce(btVector3(player->getForwardDir().x, 0, player->getForwardDir().z)* koopaBody->getMass() * 1000);
                return;
			}
            player->setPlayerHealth(player->getPlayerHealth() - 1);


            if (player->getPlayerHealth() > 0) {
                player->setIsvincible(true);

                player->setInvincibilityTimer(player->getInvincibilityDuration());
                player->setPlayerAnimationState(PlayerAnimationState::HIT); // Trigger hit animation
            }
        }
    }


    if (objectType2.substr(0, 6) == "Player" && objectType1 == "Block-Flagpole")
    {
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);
		Flagpole* block = dynamic_cast<Flagpole*>(obj1);


		player->setPlayerAnimationState(PlayerAnimationState::WIN);
		m_dynamicsWorld->removeRigidBody(player->getRigidBody().get());
		EventManager::getInstance().notify(std::make_shared<WinEvent>());
    }

    if (objectType1 == "Item-Fire" && objectType2.substr(0, 6) == "Player")
    {
        PlayerData* player = dynamic_cast<PlayerData*>(obj2);


        if (!player->getIsvincible())
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
