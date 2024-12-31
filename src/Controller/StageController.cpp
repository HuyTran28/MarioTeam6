#include "StageController.h"
#include <iostream>
#include <raymath.h> 

void StageController::moveEnemy(std::shared_ptr<Enemy> enemyData, std::shared_ptr<PlayerData> playerData)
{
    Vector3 targetPos;
    if (enemyData->getState() == EnemyState::PATROL) {
        targetPos = enemyData->getMovingToA() ? enemyData->getPointA() : enemyData->getPointB();
    }
    else if (enemyData->getState() == EnemyState::CHASE) {
        targetPos = playerData->getPlayerPos(); // Use the player's position as the target
    }
    else return;
    enemyData->setTargetPosistion(targetPos);

    rotateEnemy(enemyData);
    moveToEnemy(enemyData);

    // Check if the enemy has reached the target position with some tolerance
    float distance = Vector3Distance(enemyData->getPlayerPos(), targetPos);

    if (enemyData->getState() == EnemyState::PATROL && distance < 2.0f) {
        enemyData->setMovingToA(!(enemyData->getMovingToA()));
        Vector3 newtargetPos = enemyData->getMovingToA() ? enemyData->getPointA() : enemyData->getPointB();
        enemyData->setTargetPosistion(newtargetPos);

        rotateEnemy(enemyData);
    }
    //Vector3 dir = Vector3Subtract(targetPos, enemyData->getPlayerPos());
    //dir.y = 0;
    //dir = Vector3Normalize(dir);
    //enemyData->setForwardDir(dir);
}

void StageController::moveToEnemy(std::shared_ptr<Enemy> enemyData)
{
    Vector3 direction = Vector3Normalize(enemyData->getTargetPosition() - enemyData->getPlayerPos());
    btVector3 desiredVelocity(direction.x, 0, direction.z);

    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 1000.0f; // Higher values mean faster acceleration
    btVector3 currentVelocity = enemyData->getRigidBody()->getLinearVelocity();
    btVector3 velocityDifference = desiredVelocity * enemyData->getMoveSpeed() - currentVelocity;

    // Calculate the acceleration (delta velocity over time)
    btVector3 acceleration = velocityDifference * accelerationFactor * GetFrameTime();

    // Apply force to the enemy based on their mass and the acceleration
    btRigidBody* rigidBody = enemyData->getRigidBody().get();
    btScalar mass = rigidBody->getMass();
    btVector3 force = acceleration * mass;

    // Apply the force to the rigid body
    rigidBody->applyCentralForce(force);

    // Update position
    btTransform trans;
    enemyData->getRigidBody()->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    Vector3 newPos = { pos.x(), pos.y(), pos.z() };
    enemyData->setPlayerPos(newPos);
}

void StageController::rotateEnemy(std::shared_ptr<Enemy> enemyData)
{
    // Step 1: Calculate the desired horizontal direction
    btTransform transform = enemyData->getRigidBody()->getWorldTransform();
    btQuaternion currentRotation = transform.getRotation();

    Vector3 desiredDirection = Vector3Subtract(enemyData->getTargetPosition(), enemyData->getPlayerPos());
    desiredDirection.y = 0; // Ignore vertical component
    if (Vector3Length(desiredDirection) < 0.001f) return; // Avoid division by zero
    desiredDirection = Vector3Normalize(desiredDirection);

    // Step 2: Get the current forward direction (projected on the horizontal plane)
    Vector3 normalizedForwardDir = Vector3Normalize(enemyData->getForwardDir());
    Vector3 currentForwardDir = { normalizedForwardDir.x, 0.0f, normalizedForwardDir.z };
    currentForwardDir = Vector3Normalize(currentForwardDir);

    // Step 3: Calculate the rotation axis
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f }; // Constrain rotation to the Y-axis

    // Step 4: Calculate the rotation angle
    float dot = Vector3DotProduct(currentForwardDir, desiredDirection);
    float angle = acosf(Clamp(dot, -1.0f, 1.0f)); // Clamp for safety

    // Determine the sign of the angle using the cross product
    Vector3 cross = Vector3CrossProduct(currentForwardDir, desiredDirection);
    if (cross.y < 0) angle = -angle; // Clockwise rotation

    // Step 5: Apply the rotation
    if (fabs(angle) > 0.01f) { // Skip tiny rotations
        // Calculate smooth interpolation factor based on the angle
        float rotationSpeedFactor = fminf(fabs(angle) / 3.14159f, 1.0f); // Cap at 1.0 for maximum speed
        float slerpFactor = 0.1f + (rotationSpeedFactor * 0.4f); // Smooth factor (adjust as needed)

        btQuaternion rotation(btVector3(rotationAxis.x, rotationAxis.y, rotationAxis.z), angle);
        btQuaternion newRotation = rotation * currentRotation;

        // Smoothly interpolate the rotation
        btQuaternion interpolatedRotation = slerp(currentRotation, newRotation, slerpFactor); // Adjust factor as needed
        interpolatedRotation.normalize(); // Normalize to avoid numerical errors

        // Update transform (preserve position)
        //btVector3 currentPosition = transform.getOrigin();
        transform.setRotation(interpolatedRotation);
        //transform.setOrigin(currentPosition);

        // Apply to rigid body
        enemyData->setWorldTransform(transform);

        // Update the forward direction
        btVector3 forwardDir = transform.getBasis() * btVector3(0, 0, 1); // Assuming forward direction is along the Z-axis
        enemyData->setForwardDir(Vector3{ forwardDir.x(), 0.0f, forwardDir.z()});

    }
    enemyData->setPlayerRotationAngle(angle);
}   
    
void StageController::updateMovementOfEnemy(std::vector<std::shared_ptr<Enemy>> enemies, Camera3D cam, std::shared_ptr<PlayerData> playerData)
{
    for (auto &enemy : enemies)
    {
        if (enemy->getState() == EnemyState::SHELL)
        {
            updateCollisionShape(enemy);  // Update collision shape
            updateModelTransform(enemy);  // Synchronize marioData with physics body
            continue;
        }
        float distanceToPlayer = Vector3Distance(enemy->getPlayerPos(), playerData->getPlayerPos());
	    
        if (distanceToPlayer < 10.0f) {
			enemy->setState(EnemyState::CHASE);
		}
		else {
			enemy->setState(EnemyState::PATROL);
		}
        
        moveEnemy(enemy, playerData);
        updateCollisionShape(enemy);  // Update collision shape
        updateModelTransform(enemy);  // Synchronize marioData with physics body
        updateAnimationState(enemy, cam);
    }
     
}


void StageController::updateMovementOfBoomerang(std::shared_ptr<Boomerang> boomerang)
{
    Vector3 movement = Vector3Scale(boomerang->getForwarDir(), boomerang->getSpeed() * GetFrameTime());
    boomerang->setTravelDis(boomerang->getTravelDistance() + Vector3Length(movement));


    if (boomerang->getTravelDistance() >= boomerang->getDistance())
    {
        boomerang->setIsreturning(true);
        boomerang->setForwarDir(Vector3Scale(boomerang->getForwarDir(), -1.0f));
        boomerang->setTravelDis(0.0f);
    }


    btTransform transform;
    boomerang->getRigidBody()->getMotionState()->getWorldTransform(transform);
    btVector3 origin = transform.getOrigin();
    origin += btVector3(movement.x, movement.y, movement.z);
    transform.setOrigin(origin);
    boomerang->setRigidBodyTransform(transform);


    boomerang->setRotationAngle(fmod(boomerang->getRotationAngle() + (360.f * GetFrameTime()), 360.0f));
    btQuaternion rotation(btVector3(0, 1, 0), btRadians(boomerang->getRotationAngle()));
    transform.setRotation(rotation);
    boomerang->setRigidBodyTransform(transform);


    btVector3 pos = transform.getOrigin();
    boomerang->setPosition({ (float)pos.getX(), (float)pos.getY(), (float)pos.getZ() });
}

void StageController::updateMovementOfFire(std::shared_ptr<Fire> fire)
{
    Vector3 movement = Vector3Scale(fire->getForwarDir(), fire->getSpeed() * GetFrameTime());
    fire->setTravelDis(fire->getTravelDistance() + Vector3Length(movement));


    if (fire->getTravelDistance() >= fire->getDistance())
    {
        fire->setIsreturning(true);
        fire->setForwarDir(Vector3Scale(fire->getForwarDir(), -1.0f));
        fire->setTravelDis(0.0f);
    }


    btTransform transform;
    fire->getRigidBody()->getMotionState()->getWorldTransform(transform);
    btVector3 origin = transform.getOrigin();
    origin += btVector3(movement.x, movement.y, movement.z);
    transform.setOrigin(origin);
    fire->setRigidBodyTransform(transform);

        
    fire->setRotationAngle(fmod(fire->getRotationAngle() + (360.f * GetFrameTime()), 360.0f));
    btQuaternion rotation(btVector3(0, 1, 0), btRadians(fire->getRotationAngle()));
    transform.setRotation(rotation);
    fire->setRigidBodyTransform(transform);


    btVector3 pos = transform.getOrigin();
    fire->setPosition({ (float)pos.getX(), (float)pos.getY(), (float)pos.getZ() });

}

void StageController::updateTimeFire(std::shared_ptr<Enemy> bowser, std::shared_ptr<Fire> fire)
{
    float deltaTime = GetFrameTime();

    // Update the throw timer
    if (bowser->getThrowTimer() > 0.0f) {
        bowser->setThrowTimer(bowser->getThrowTimer() - deltaTime);
    }
    else {
        bowser->setIsThrowing(false);
    }

    if (bowser->getIsUsed()) {
        // Get Bowser's forward direction
        Vector3 forwardDir = bowser->getForwardDir();
        if (Vector3Length(forwardDir) == 0.0f) {
            forwardDir = { 1.0f, 0.0f, 0.0f }; // Default direction if Bowser's forwardDir is invalid
        }

        float duration = std::max(0.0f, bowser->getTimeFire() - deltaTime);
        bowser->setTimeFire(duration);

        if (!fire->getIsvisble()) {
            // Notify event
            EventManager::getInstance().notify(std::make_shared<FireEvent>());

            // Calculate starting position and direction
            Vector3 pos = Vector3Add(
                Vector3Add(bowser->getPlayerPos(), { 5.0f, 4.0f, 5.0f }),
                Vector3Scale(forwardDir, 1.5f)
            );
            fire->setStartPos(pos);
            fire->setPosition(pos);
            fire->setForwarDir(forwardDir); // Set forward direction of the fire
            fire->setIsVisble(true);

            // Set initial rigid body transform
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(fire->getStartPos().x, fire->getStartPos().y, fire->getStartPos().z));
            fire->setRigidBodyTransform(transform);

            // Reset the throw timer
            bowser->setThrowTimer(0.5f); // Set the cooldown duration as needed
            bowser->setIsThrowing(true);
        }

        if (fire->getIsvisble()) {
            if (fire->getIsreturning()) {
                fire->setIsVisble(false);
                fire->setIsreturning(false);

                btTransform transform;
                transform.setIdentity();
                transform.setOrigin(btVector3(0.0f, -50.0f, 0.0f));
                fire->setRigidBodyTransform(transform);
                fire->setTravelDis(0.0f);
            }
            else {
                updateMovementOfFire(fire);
            }
        }

        if (duration <= 0) {
            bowser->setIsUsed(false);
            bowser->setTimeFire(0.0f);
            fire->setIsVisble(false);
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0.0f, -50.0f, 0.0f));
            fire->setRigidBodyTransform(transform);
        }
    }
}



void StageController::updateTimeBoomerang(std::shared_ptr<PlayerData> playerData, std::shared_ptr<Boomerang> boomerang)
{
    float deltaTime = GetFrameTime();

    // Update the throw timer
    if (playerData->getThrowTimer() > 0.0f) {
        playerData->setThrowTimer(playerData->getThrowTimer() - deltaTime);
    }
    else
    {
		playerData->setIsThrowing(false);
    }

    if (playerData->getIsUsed())
    {
		Vector3 forwardDir = playerData->getForwardDir();

        if (forwardDir == Vector3{ 0.0f, 0.0f, 0.0f })
        {
            forwardDir = { 1.0f, 0.0f, 0.0f };
        }

        float Duration = std::max(0.0f, playerData->getTimeOfBoomerang() - deltaTime);
        playerData->setTimeOfBoomerang(Duration);

     
        if (IsKeyPressed(KEY_J))
        {
            if (!boomerang->getIsvisble())
            {
				EventManager::getInstance().notify(std::make_shared<BoomerangEvent>());
                Vector3 pos = Vector3Add(Vector3Add(playerData->getPlayerPos(), {2.0f, 2.0f, 0.0f}), Vector3Multiply({1.5f, 1.5f, 1.5f}, forwardDir));
                boomerang->setStartPos(pos);
                boomerang->setPosition(pos);
                boomerang->setForwarDir(forwardDir);
                boomerang->setIsVisble(true);

                btTransform transform;
                transform.setIdentity();
                transform.setOrigin(btVector3(boomerang->getStartPos().x, boomerang->getStartPos().y, boomerang->getStartPos().z));
                boomerang->setRigidBodyTransform(transform);

                // Reset the throw timer
                playerData->setThrowTimer(1.0f); // Set the cooldown duration as needed
				playerData->setIsThrowing(true);
            }
        }

       
        if (boomerang->getIsvisble())
        {
            if (boomerang->getIsreturning())
            {
                if (Vector3Distance(boomerang->getPosition(), boomerang->getStartPos()) < 0.5)
                {
                    boomerang->setIsVisble(false);
                    boomerang->setIsreturning(false); 

                  
                    btTransform transform;
                    transform.setIdentity();
                    transform.setOrigin(btVector3(0.0f, -20.0f, 0.0f));
                    boomerang->setRigidBodyTransform(transform);
                    boomerang->setTravelDis(0.0f);
                }
                else
                {
                    updateMovementOfBoomerang(boomerang);
                }
            }
            else
            {
                updateMovementOfBoomerang(boomerang);
            }
        }


        if (Duration <= 0)
        {
            playerData->setIsUsed(false);
            playerData->setTimeOfBoomerang(0.0f);
            boomerang->setIsVisble(false);
            btTransform transform;
            transform.setIdentity();
            transform.setOrigin(btVector3(0.0f, -20.0f, 0.0f));
            boomerang->setRigidBodyTransform(transform);
        }
    }
}


void StageController::updateBounceOfBlock(std::shared_ptr<BlockData> blockData)
{
    float deltaTime = GetFrameTime();
    if (blockData->getIsBouncing())
    {
        btTransform blockTransform;
        blockData->getRigidBody()->getMotionState()->getWorldTransform(blockTransform);
        btVector3 originPosition = blockTransform.getOrigin();

        float height = VELOCITY * (blockData->getBounceTime() * blockData->getBounceTime() - TILE_DURATION * blockData->getBounceTime());


        blockTransform.setOrigin(btVector3(
            originPosition.x(),
            originPosition.y() - height, //update position of block 
            originPosition.z()
        ));
        blockData->setWorldTransform(blockTransform);

        //decrease time bounce
        float tmp = blockData->getBounceTime() - deltaTime;
        blockData->setBouncetime(tmp);

        btVector3 position = blockTransform.getOrigin();
        if (blockData->getBounceTime() <= 0)
        {
            blockData->setIsBounce(false);
            blockData->setBouncetime(0.0f);
            blockTransform.setOrigin(btVector3(blockData->getPosition().x, blockData->getPosition().y, blockData->getPosition().z));
            blockData->setWorldTransform(blockTransform);

        }
    }
}

void StageController::updateInvincibilityTimer(std::shared_ptr<PlayerData> playerData)
{
    if (playerData->getIsvincible()) {
        float tmp = playerData->getInvincibilityTimer() - GetFrameTime();
        playerData->setInvincibilityTimer(tmp);
        if (playerData->getInvincibilityTimer() <= 0.0f) {
            playerData->setIsvincible(false);
       
            if (playerData->getPlayerAnimationState() == PlayerAnimationState::HIT) {
                if (playerData->getIsOnGround())
                {
                    playerData->setPlayerAnimationState(PlayerAnimationState::IDLE);
                }
                else
                    playerData->setPlayerAnimationState(PlayerAnimationState::FALLING);
            }
        }
    }
}


void StageController::updateBlock(BlockData* preBlock, std::shared_ptr<BlockData> newBlock, std::vector<std::shared_ptr<BlockData>>& map, std::vector<std::shared_ptr<ItemData>>& items)
{

    auto it = std::find_if(map.begin(), map.end(), [preBlock](const std::shared_ptr<BlockData>& block) {
        return block.get() == preBlock;
        });

    btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
    if (it != map.end()) {
        map.erase(it);
        CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
    }
    if (newBlock)
    {
        Vector3 newPosition = newBlock->getPosition();
        newPosition.y += 3.0f;
        int randomChoice = std::rand() % 8;

        std::shared_ptr<ItemData> item = nullptr;

        if (randomChoice == 7) {
       
            item = ItemFactory::createItem(
                ItemType::RED_MUSHROOM,
                newPosition,
                "../../Assets\\Models\\Items\\RedMushroom.glb",
                { 1.0f, 1.0f, 1.0f },
                { 0.0, 1.0f, 0.0f },
                0.0f,
                CollisionManager::getInstance()->getDynamicsWorld()
            );
        }
        else if (randomChoice == 6)
        {
            item = ItemFactory::createItem(
                ItemType::PURPLE_MUSHROOM,
                newPosition,
                "../../Assets\\Models\\Items\\PurpleMushroom.glb",
                { 1.0f, 1.0f, 1.0f },
                { 0.0, 1.0f, 0.0f },
                0.0f,
                CollisionManager::getInstance()->getDynamicsWorld()
            );
        }
        else if (randomChoice == 5)
        {
            item = ItemFactory::createItem(
                ItemType::GREEN_MUSHROOM,
                newPosition,
                "../../Assets\\Models\\Items\\GreenMushroom.glb",
                { 1.0f, 1.0f, 1.0f },
                { 0.0, 1.0f, 0.0f },
                0.0f,
                CollisionManager::getInstance()->getDynamicsWorld()
            );
        }
        else if (randomChoice == 4)
        {
            item = ItemFactory::createItem(
                ItemType::BOOMERANG_FLOWER,
                newPosition,
                "../../Assets\\Models\\Items\\BoomerangFlower.glb",
                { 1.0f, 1.0f, 1.0f },
                { 0.0, 1.0f, 0.0f },
                0.0f,
                CollisionManager::getInstance()->getDynamicsWorld()
            );
        }
        else {
         
            item = ItemFactory::createItem(
                ItemType::COIN,
                newPosition,
                "../../Assets\\Models\\Items\\Coin.glb",
                { 1.0f, 1.0f, 1.0f },
                { 0.0, 1.0f, 0.0f },
                0.0f,
                CollisionManager::getInstance()->getDynamicsWorld()
            );
        }

        map.push_back(newBlock);
        items.push_back(item);
        
    }

    CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability

}

void StageController::updateEnemy(Enemy* preEnemy, std::shared_ptr<Enemy> newEnemy, std::vector<std::shared_ptr<Enemy>>& enemies)
{
	auto it = std::find_if(enemies.begin(), enemies.end(), [preEnemy](const std::shared_ptr<Enemy>& enemy) {
		return enemy.get() == preEnemy;
		});

	btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
	if (it != enemies.end()) {
		enemies.erase(it);
		CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
	}
	if (newEnemy)
	{
		enemies.push_back(newEnemy);
	}

	CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
}

void StageController::registerSelf()
{
}

void StageController::updateCamera(std::shared_ptr<StageModel> model)
{
    Camera3D& camera = model->getCamera();
    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(model->getPlayerData());

    Vector3 cameraOffset = { -40.0f, 20.0f, 0.0f };
    camera.position = Vector3Add(marioModel->getPlayerPos(), cameraOffset);
    camera.target = marioModel->getPlayerPos();

    float zoomSpeed = 5.0f;
    camera.fovy -= GetMouseWheelMove() * zoomSpeed;

    if (camera.fovy < 10.0f) camera.fovy = 10.0f;
    if (camera.fovy > 90.0f) camera.fovy = 90.0f;
}

void StageController::updateTimer(float& timer)
{
    if (isInputEnable == true)
	    timer -= GetFrameTime();
}

void StageController::updateMovementOfPlayer(std::shared_ptr<PlayerData> playerData, Camera3D cam)
{

    if (playerData->getRigidBody())
    {
        playerData->setIsOnGround(checkGroundCollision(playerData));
        if (!(playerData->getIsOnGround())) {
            // Apply gravity
            btVector3 velocity = playerData->getRigidBody()->getLinearVelocity();
            btVector3 gravity = playerData->getWorld()->getGravity();
            playerData->applyCentralForce(gravity);
            // Apply extra gravity for faster falling if needed
            const float extraGravityFactor = 100.0f;
            btVector3 additionalGravity(0, extraGravityFactor * gravity.getY(), 0);

            if (velocity.getY() < 0.0f) {
                velocity.setY(0.0f);  // Prevent the player from falling through the ground
                playerData->setLinearVelocity(velocity);
                playerData->applyCentralForce(additionalGravity * playerData->getRigidBody()->getMass());
            }
        }

        if (isInputEnable)
        {
            movePlayer(playerData);    // Update movement
            jumpPlayer(playerData);  // Handle jumping
        }

        updateCollisionShape(playerData);  // Update collision shape
        updateModelTransform(playerData);  // Synchronize playerData with physics body
        setPlayerAnimationState(playerData);
        updateAnimationState(playerData, cam);  
        updateInvincibilityTimer(playerData);
    }
}

void StageController::movePlayer(std::shared_ptr<PlayerData> playerData)
{
    btVector3 desiredVelocity(0, 0, 0);

    bool isW = false;
	bool isS = false;
	bool isA = false;
	bool isD = false;

    // Calculate the desired movement direction based on input
    if (IsKeyDown(KEY_W)) {
		isW = true;
    }
	if (IsKeyDown(KEY_S)) {
		isS = true;
    }
	if(IsKeyDown(KEY_A)) {
		isA = true;
    }
	if (IsKeyDown(KEY_D)) {
		isD = true;
    }

    Vector2 newDir = { 0.0f, 0.0f };
	if (isW) newDir.y += 1.0f;
	if (isS) newDir.y -= 1.0f;
	if (isA) newDir.x -= 1.0f;
	if (isD) newDir.x += 1.0f;
    
	if (newDir == Vector2{ 0.0f, 0.0f }) {
        playerData->setPlayerRotationAngle(atan2f( 1.0f, 0.0f ));
		playerData->setForwarDir(Vector3{ 0.0f, 0.0f, 0.0f });
        desiredVelocity = btVector3(0.0f, 0.0f, 0.0f);
    }
    else {
        Vector3 newForwardDir = { newDir.y, 0.0f, newDir.x };
        playerData->setForwarDir(Vector3Normalize(newForwardDir));
        playerData->setPlayerRotationAngle(atan2f(newDir.y, newDir.x));
        desiredVelocity = btVector3(playerData->getForwardDir().x, 0, playerData->getForwardDir().z).normalized() * playerData->getMoveSpeed();
    }

    // Smooth acceleration towards the desired velocity
    const float accelerationFactor = 1000.0f; // Higher values mean faster acceleration
    btVector3 currentVelocity = playerData->getRigidBody()->getLinearVelocity();
    btVector3 velocityDifference = desiredVelocity - currentVelocity;

    // Calculate the acceleration (delta velocity over time)
    btVector3 acceleration = velocityDifference * accelerationFactor * GetFrameTime();

    // Apply force to the player based on their mass and the acceleration
    btRigidBody* rigidBody = playerData->getRigidBody().get();
    btScalar mass = rigidBody->getMass();
    btVector3 force = acceleration * mass;

    // Apply the force to the rigid body
    rigidBody->applyCentralForce(force);

    // If no input is given, stop horizontal movement (no force applied)
    if (desiredVelocity.length() == 0) {
        rigidBody->setLinearVelocity(btVector3(0, currentVelocity.y(), 0));
    }
}


void StageController::jumpPlayer(std::shared_ptr<PlayerData> playerData)
{
   
    float invGravity = 1.0f / -(playerData->getWorld())->getGravity().getY();

    if (playerData->getIsOnGround() && IsKeyDown(KEY_SPACE)) {
        playerData->setIsJumping(true);      // Start the jump
        playerData->setJumpTimer(0.0f);      // Reset the jump timer
        playerData->setIsOnGround(false);   // Player is now airborne

        // Increase the jump force for a higher jump
        float acceleration = (playerData->getJumpForce() * 1.0f) / playerData->getRigidBody()->getMass();
        playerData->setMaxJumpDuaration(sqrt(acceleration / playerData->getRigidBody()->getMass() * invGravity)); // Simplified physics calculation

        EventManager::getInstance().notify(std::make_shared<JumpEvent>());
    }

    if (playerData->getIsJumping())
    {
        // Increment the jump timer
        float jumpTimer = playerData->getJumpTimer();
        playerData->setJumpTimer(jumpTimer += GetFrameTime());
        // Calculate the current jump force based on the elapsed time
        float currentJumpForce = playerData->getJumpForce() * 2.0f * (1.0f - (playerData->getJumpTimer() / playerData->getMaxJumpDuration()));

        // Apply the current jump force

        playerData->applyCentralImpulse(btVector3(0, currentJumpForce * GetFrameTime(), 0));
        // End the jump if the max jump duration is reached
        if (playerData->getJumpTimer() >= playerData->getMaxJumpDuration()) {
            playerData->setIsJumping(false);

            btVector3 velocity = playerData->getRigidBody()->getLinearVelocity();
            velocity.setY(0.0f);  // Prevent the player from falling through the ground
            playerData->setLinearVelocity(velocity);
        }
    }

}

void StageController::updateBigDuration(std::shared_ptr<PlayerData> playerData)
{
	if (playerData->getIsBig())
	{
		float bigDuration = playerData->getBigDuration();
		bigDuration -= GetFrameTime();
		playerData->setBigDuration(bigDuration);
		if (bigDuration <= 0)
		{
			playerData->setIsBig(false);
			playerData->setBigDuration(0.0f);
            playerData->setPlayerScale(Vector3Multiply(playerData->getPlayerScale(), Vector3{ 1.0f / 1.25f, 1.0f / 1.25f, 1.0f / 1.25f }));
            playerData->setObjectType("Player-Normal");
		}
	}
}

void StageController::updateSpecial(std::shared_ptr<PlayerData> playerData)
{
    if (playerData->getIsSpecial())
    {
        float specialDuration = playerData->getSpecialTimer();
        specialDuration -= GetFrameTime();
        playerData->setSpecialTimer(specialDuration);
        if (specialDuration <= 0)
        {
            playerData->setIsSpecial(false);
            playerData->setSpecialTimer(0.0f);
            playerData->setMoveSpeed(playerData->getMoveSpeed() / 2.0f);
            playerData->setObjectType("Player-Normal");
        }
    }
}

void StageController::updateScore(std::shared_ptr<Event> event, std::shared_ptr<StageModel> model)
{
	if (event->getType() == "Item Touched Event")
	{
		auto itemTouched = std::dynamic_pointer_cast<ItemTouchedEvent>(event);
        if (itemTouched->getObjectType() == "Item-Coin")
		{
            model->setScore(model->getScore() + 100);
        }
        else if (itemTouched->getObjectType() != "Item-PurpleMushroom") {
            model->setScore(model->getScore() + 1000);
        }
	}
	else if (event->getType() == "Enemy Die Event")
	{
		model->setScore(model->getScore() + 500);
	}
	else if (event->getType() == "Block Change Event")
	{
		auto blockChange = std::dynamic_pointer_cast<BlockChangeEvent>(event);
        if (blockChange->getPreType() == "Block-Question")
        {
			model->setScore(model->getScore() + 200);
        }
		else if (blockChange->getNewType() == "" && blockChange->getPreType() != "Block-Flagpole")
		{
			model->setScore(model->getScore() + 20);
		}
	}
    else if (event->getType() == "Enemy Change Event")
    {
		model->setScore(model->getScore() + 500);
    }
    GameData::getInstance().setPlayerScore(model->getScore());
}

void StageController::updatePauseAndSetting(std::shared_ptr<Button> setting, std::shared_ptr<Button> pause)
{
    if (pause->isClicked(GetMousePosition()))
    {

        EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Pause"));
        return;
    }
    if (setting->isClicked(GetMousePosition()))
    {
        EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Setting"));
        return;
    }
}

void StageController::removeItem(std::vector<std::shared_ptr<ItemData>>& items, ItemData* item)
{
    auto it = std::find_if(items.begin(), items.end(), [item](const std::shared_ptr<ItemData>& block) {
        return block.get() == item;
        });

    if (it != items.end()) {
        items.erase(it);
        //btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
        //CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
    }

}

void StageController::removeEnemy(std::vector<std::shared_ptr<Enemy>>& enemies, Enemy* enemy)
{
    auto it = std::find_if(enemies.begin(), enemies.end(), [enemy](const std::shared_ptr<Enemy>& en) {
        return en.get() == enemy;
        });

	if (it != enemies.end()) {
		enemies.erase(it);
		//btScalar deltaTime = 1.0f / 60.0f; // For 60 FPS
		//CollisionManager::getInstance()->getDynamicsWorld()->stepSimulation(deltaTime, 10); // Max 10 substeps for stability
	}
}

void StageController::updatePlayerDie(std::shared_ptr<PlayerData> playerData)
{
    if (playerData->getPlayerHealth() <= 0)
    {
        if (isNotifyDie == true)
        {
			return;
        }

		isNotifyDie = true;
        isInputEnable = false;
        
        playerData->setPlayerAnimationState(PlayerAnimationState::DIE);
		playerData->setPlayerHealth(0);
		playerData->setForwarDir(Vector3{ 0.0f, 0.0f, 0.0f });

        EventManager::getInstance().notify(std::make_shared<DieEvent>());
    }
}




void StageController::updateCollisionShape(std::shared_ptr<CharacterData> characterData)
{
    // Get the rigid body's current transform
    btTransform transform = characterData->getRigidBody()->getWorldTransform();

    // Force the rotation to align with the Y-axis (capsule's up-axis)
    transform.setRotation(btQuaternion(0, 0, 0, 1));
    characterData->setRigidBodyTransform(transform);
}

void StageController::updateModelTransform(std::shared_ptr<CharacterData> characterData)
{
    // Get the rigid body's transform
    btTransform transform = characterData->getRigidBody()->getWorldTransform();
    btVector3 origin = transform.getOrigin();

    // Get the bounding box of the marioData
    BoundingBox marioDataBounds = GetModelBoundingBox(characterData->getPlayerModel());
    float marioDataHeight = (marioDataBounds.max.y - marioDataBounds.min.y) * characterData->getPlayerScale().y;

    // Retrieve the collision shape and calculate capsule dimensions
    btCollisionShape* collisionShape = characterData->getRigidBody()->getCollisionShape();
    btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(collisionShape);
    float capsuleRadius = capsuleShape->getRadius();
    float capsuleHeight = capsuleShape->getHalfHeight() * 2.0f + capsuleRadius * 2.0f;

    // Calculate the vertical offset to align the marioData's center with the capsule's center
    float yOffset = (capsuleHeight / 2) - capsuleRadius * 1.7f - (marioDataHeight / 2);

    // Update the marioData position
    characterData->setPlayerPos({ origin.getX(), origin.getY() + yOffset, origin.getZ() });

    // Apply rotation and scale to the marioData
    Matrix rotationMatrix = MatrixRotateY(characterData->getPlayerRotationAngle());
    Matrix scaleMatrix = MatrixScale(characterData->getPlayerScale().x, characterData->getPlayerScale().y, characterData->getPlayerScale().z);

    // Combine the transformations and apply to the marioData

    characterData->setPlayerModelTransform(MatrixMultiply(scaleMatrix, rotationMatrix));
}

bool StageController::checkGroundCollision(std::shared_ptr<CharacterData> characterData)
{
    
    if (characterData->getRigidBody()) {
        // Get the current motion state of the rigid body
        btTransform transform;
        characterData->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Perform a raycast below the character to check for ground
        btVector3 start = transform.getOrigin();
        btVector3 end = start - btVector3(0, 2.2f, 0);

        btCollisionWorld::ClosestRayResultCallback rayCallback(start, end);
        characterData->getWorld()->rayTest(start, end, rayCallback);

        if (rayCallback.hasHit()) {
            // If the ray hits something, we are on the ground
            return true;
        }
    }
    return false;
}


void StageController::updateAnimationState(std::shared_ptr<CharacterData> characterData, Camera3D cam)
{
	if ((Vector3Distance(cam.position, characterData->getPlayerPos()) > 80.0f && cam.position.x < characterData->getPlayerPos().x)
        || (Vector3Distance(cam.position, characterData->getPlayerPos()) > 10.0f && cam.position.x > characterData->getPlayerPos().x)) {
		return; // Skip animation updates for distant objects
	}

    PlayerAnimationState animationState = characterData->getPlayerAnimationState();

    switch (animationState) {
    case PlayerAnimationState::IDLE:
        AnimationManager::getInstance().playAnimation(3, characterData);
        break;

    case PlayerAnimationState::WALKING:
        AnimationManager::getInstance().playAnimation(5, characterData);

        break;

    case PlayerAnimationState::JUMPING:
        AnimationManager::getInstance().playAnimation(4, characterData);

        break;

    case PlayerAnimationState::FALLING:
        AnimationManager::getInstance().playAnimation(1, characterData);

        break;

    case PlayerAnimationState::HIT:
        AnimationManager::getInstance().playAnimation(2, characterData);

        break;
    case PlayerAnimationState::DIE:
       
        AnimationManager::getInstance().playAnimation(0, characterData);

        break;
    case PlayerAnimationState::WIN:

        AnimationManager::getInstance().playAnimation(6, characterData);

        break;
	case PlayerAnimationState::THROW:
		AnimationManager::getInstance().playAnimation(7, characterData);
		break;
    }
    // Update the animation frame
   
    AnimationManager::getInstance().updateAnimation(GetFrameTime(), characterData);

}

void StageController::setPlayerAnimationState(std::shared_ptr<CharacterData> characterData)
{
    std::shared_ptr<PlayerData> playerData = std::dynamic_pointer_cast<PlayerData>(characterData);
    if (characterData->getPlayerAnimationState() == PlayerAnimationState::DIE || characterData->getPlayerAnimationState() == PlayerAnimationState::WIN) {
        return;
    }

    if (playerData->getIsvincible() && playerData->getPlayerAnimationState() == PlayerAnimationState::HIT) {
        return; 
    }

	if (playerData->getIsThrowing())
	{
		characterData->setPlayerAnimationState(PlayerAnimationState::THROW);
		return;
	}

    btVector3 velocity = characterData->getRigidBody()->getLinearVelocity();
    if (!(characterData->getIsOnGround())) {
        // Mario is airborne
        if (velocity.getY() > 0.01f) {
            // Ascending (jumping up)
            characterData->setPlayerAnimationState(PlayerAnimationState::JUMPING);
        }
        else if (velocity.getY() <= 0.0f) {
            // Descending (falling down)
            characterData->setPlayerAnimationState(PlayerAnimationState::FALLING);
        }
    }
    else {

        // Player is grounded
        if (velocity.length() > 0.1f) {

            characterData->setPlayerAnimationState(PlayerAnimationState::WALKING);
        }
        else {

            characterData->setPlayerAnimationState(PlayerAnimationState::IDLE);
        }
    }
}
