#include "StageModel.h"
#include <iostream>

void StageModel::saveFile(std::string name)
{
    Camera3D m_camera = getCamera();

    std::ofstream file;
    file.open(name);
    if (file.is_open())
    {
		file << score << " " << timer << " " << coins << " " << countFire << std::endl;

		file << "Player" << std::endl;
		m_playerData->save(file);
        file << std::endl;

        file << "Camera" << std::endl;
        file << m_cameraInitialPosition.x << " " << m_cameraInitialPosition.y << " " << m_cameraInitialPosition.z << " ";
        file << m_camera.target.x << " " << m_camera.target.y << " " << m_camera.target.z << " ";
        file << m_camera.fovy << " ";
        file << m_camera.projection << std::endl;

        file << "Map" << std::endl;
        for (auto& block : m_map)
        {
			block->save(file);
			file << std::endl;
        }
        file << "Enemies" << std::endl;
        for (auto& enemy : m_enemies)
        {
			enemy->save(file);
			file << std::endl;
        }
        file << "Items" << std::endl;
        for (auto& item : m_items)
        {
			item->save(file);
			file << std::endl;
        }
		file << "Boomerang" << std::endl;
		m_boomerang->save(file);
    }
}


void StageModel::loadFile()
{
    std::ifstream file;
	std::string nameFile = "../../Save/" + GameData::getInstance().getCurState() + ".txt";
    file.open(nameFile);
    if (file.is_open())
	{
		std::string line;

		std::getline(file, line);
		std::istringstream iss2(line);
		iss2 >> score >> timer >> coins >> countFire;

		std::getline(file, line);
		if (line != "Player")
			return;

		std::shared_ptr<PlayerData> playerData = std::make_shared<PlayerData>();
		playerData->load(file);
		m_playerData = createMarioModel(playerData->getPlayerPos(), playerData->getPlayerScale());

		m_playerData->setForwarDir(playerData->getForwardDir());
		m_playerData->setIsOnGround(playerData->getIsOnGround());
		m_playerData->setVelocity(playerData->getVelocity());
		m_playerData->setIsUsed(playerData->getIsUsed());
		m_playerData->setTimeOfBoomerang(playerData->getTimeOfBoomerang());
		m_playerData->setPlayerHealth(playerData->getPlayerHealth());
		m_playerData->setPlayerScale(playerData->getPlayerScale());
		m_playerData->setPlayerRotationAxis(playerData->getPlayerRotationAxis());
		m_playerData->setPlayerRotationAngle(playerData->getPlayerRotationAngle());
		m_playerData->setMoveSpeed(playerData->getMoveSpeed());
		m_playerData->setIsJumping(playerData->getIsJumping());
		m_playerData->setIsCrouching(playerData->getIsCrouching());
		m_playerData->setJumpForce(playerData->getJumpForce());
		m_playerData->setJumpTimer(playerData->getJumpTimer());
		m_playerData->setMaxJumpDuaration(playerData->getMaxJumpDuration());
		m_playerData->setIsBig(playerData->getIsBig());
		m_playerData->setBigDuration(playerData->getBigDuration());
		m_playerData->setInvincibilityTimer(playerData->getInvincibilityTimer());
		m_playerData->setIsvincible(playerData->getIsvincible());
		m_playerData->setInvincibilityDuration(playerData->getInvincibilityDuration());
		m_playerData->setIsThrowing(playerData->getIsThrowing());
		m_playerData->setThrowDuration(playerData->getThrowDuration());
		m_playerData->setThrowTimer(playerData->getThrowTimer());
		m_playerData->setIsSpecial(playerData->getIsSpecial());
		m_playerData->setSpecialTimer(playerData->getSpecialTimer());
		m_playerData->setSpecialDuration(playerData->getSpecialDuration());


        file.ignore();

        std::getline(file, line);

        if (line != "Camera")
            return;

        std::getline(file, line);
        std::istringstream iss(line);

		// Handle camera
        float x, y, z;
        iss >> x >> y >> z;
        Vector3 cameraInitPos = { x, y, z };
        iss >> x >> y >> z;
        Vector3 cameraTarget = { x, y, z };
        float fovy;
        iss >> fovy;
        int cameraMode;
        iss >> cameraMode;
        Camera3D camera = { cameraInitPos, cameraTarget, Vector3{0.0f, 1.0f, 0.0f}, fovy, (CameraProjection)cameraMode };
        setCamera(camera);

        std::getline(file, line);
		if (line != "Map")
			return;

        std::vector<std::shared_ptr<BlockData>> map;

        while (std::getline(file, line) && line.substr(0, 5) == "Block")
        {
            std::istringstream iss(line);
            std::string blockType;
            iss >> blockType;
            BlockType type;
            std::string path = "";
            if (blockType == "Block-Normal-Brick")
            {
                type = BlockType::BrickBlock;
                path = PATH_BRICKBLOCK;
            }
            else if (blockType == "Block-Normal-Fly")
            {
                type = BlockType::FlyBlock;
                path = PATH_FLYBLOCK;
            }
            else if (blockType == "Block-Normal-Ground")
            {
                type = BlockType::GroundBlock;
                path = PATH_GROUNDBLOCK;
            }
            else if (blockType == "Block-Normal-Roulette")
            {
                type = BlockType::RouletteBlock;
                path = PATH_ROULETTEBLOCK;
            }
            else if (blockType == "Block-Normal-Wall1")
            {
                type = BlockType::WallBlock1;
                path = PATH_WALLBLOCK1;
            }
            else if (blockType == "Block-Normal-Wall2")
            {
                type = BlockType::WallBlock2;
                path = PATH_WALLBLOCK2;
            }
            else if (blockType == "Block-Normal-Wall3")
            {
                type = BlockType::WallBlock3;
                path = PATH_WALLBLOCK3;
            }
            else if (blockType == "Block-Normal-Wall4")
            {
                type = BlockType::WallBlock4;
                path = PATH_WALLBLOCK4;
            }
            else if (blockType == "Block-Normal-Wall5")
            {
                type = BlockType::WallBlock5;
                path = PATH_WALLBLOCK5;
            }
            else if (blockType == "Block-Empty")
            {
                type = BlockType::EmptyBlock;
                path = PATH_EMPTYBLOCK;
            }
            else if (blockType == "Block-Question")
            {
                type = BlockType::QuestionBlock;
                path = PATH_QUESTIONBLOCK;
            }
            else if (blockType == "Block-Flagpole")
            {
                type = BlockType::Flagpole;
                path = PATH_ISLANDBLOCK;
            }
            else if (blockType == "Block-NormalBrickBlock")
            {
                type = BlockType::NormalBrickBlock;
                path = PATH_NORMALBRICKBLOCK;
            }
            else if (blockType == "Block-Pipe")
            {
                type = BlockType::PipeBlock;
                path = PATH_PIPEBLOCK;
            }
            else if (blockType == "Block-UpPipe")
            {
                type = BlockType::SupportivePipeBlock;
                path = PATH_SUPPORTIVEPIPEBLOCK;
            }

            if (path == "")
                break;
            
			iss >> x >> y >> z;
			Vector3 position = { x, y, z };
			iss >> x >> y >> z;
			Vector3 scale = { x, y, z };
			iss >> x >> y >> z;
			Vector3 rotationAxis = { x, y, z };
			float rotationAngle;
			iss >> rotationAngle;
			bool isBouncing;
			iss >> isBouncing;
			float bounceTime;
			iss >> bounceTime;

            std::shared_ptr<BlockData> block = BlockFactory::createBlock(type, CollisionManager::getInstance()->getDynamicsWorld(), path, position, scale, rotationAxis, rotationAngle);

			block->setBouncetime(bounceTime);
			block->setIsBounce(isBouncing);

			if (blockType == "Block-Pipe")
			{
				iss >> x >> y >> z;
				Vector3 position2 = { x, y, z };
				auto pipeBlock = std::dynamic_pointer_cast<PipeBlock>(block);
				pipeBlock->setNewPosition(btVector3{position2.x, position2.y, position2.z});
			}
            else if (blockType == "Block-UpPipe")
            {
                iss >> x >> y >> z;
                Vector3 position2 = { x, y, z };
                auto pipeBlock = std::dynamic_pointer_cast<SupportivePipeBLock>(block);
                pipeBlock->setNewPosition(btVector3{ position2.x, position2.y, position2.z });
            }
            map.push_back(block);
        }
		m_map = map;

        std::vector<std::shared_ptr<Enemy>> enemies;

        while (std::getline(file, line) && line.substr(0, 5) == "Enemy")
        {
            std::istringstream iss(line);
            std::string enemyType;
            iss >> enemyType;
            EnemyType type;
            std::string path = "";

            if (enemyType == "Enemy-Goomba")
            {
                type = EnemyType::Goomba;
                path = PATH_GOOMBA;
            }
            else if (enemyType == "Enemy-Koopa")
            {
                type = EnemyType::Koopa;
                path = PATH_KOOPA;
            }
            else if (enemyType == "Enemy-Bowser")
            {
                type = EnemyType::Bowser;
                path = PATH_BOWSER;
            }

            if (path == "")
                break;

            float x, y, z;
            iss >> x >> y >> z;

			Vector3 forwardDir = { x, y, z };
			bool isOnGround;
			iss >> isOnGround;
			iss >> x >> y >> z;
			Vector3 velocity = { x, y, z };
			bool isUsed;
			iss >> isUsed;
			float timeBoomerang;
			iss >> timeBoomerang;
			iss >> x >> y >> z;
			Vector3 position = { x, y, z };
			int health;
			iss >> health;
			iss >> x >> y >> z;
			Vector3 scale = { x, y, z };
			iss >> x >> y >> z;
			Vector3 rotationAxis = { x, y, z };
			float rotationAngle;
			iss >> rotationAngle;
			float speed;
            iss >> speed;
            Vector3 pointA;
			iss >> x >> y >> z;
			pointA = { x, y, z };
			Vector3 pointB;
			iss >> x >> y >> z;
			pointB = { x, y, z };
			bool movingToA;
			iss >> movingToA;
			bool isDie;
			iss >> isDie;

            std::shared_ptr<Enemy> enemy = EnemyFactory::createEnemy(type, CollisionManager::getInstance()->getDynamicsWorld(), path, position, forwardDir, rotationAxis, rotationAngle, scale, speed, pointA, pointB);

			enemy->setIsOnGround(isOnGround);
			enemy->setVelocity(velocity);
            enemy->setIsUsed(isUsed);
			enemy->setTimeOfBoomerang(timeBoomerang);
			enemy->setMovingToA(movingToA);
			enemy->setIsDie(isDie);
			enemy->setPlayerHealth(health);

            if (enemyType == "Enemy-Koopa")
            {
				std::string state;
				iss >> state;
				auto koopa = std::dynamic_pointer_cast<Koopa>(enemy);
				koopa->setState(state);
            }
			enemies.push_back(enemy);
        }
		m_enemies = enemies;

        std::vector<std::shared_ptr<ItemData>> items;

        while (std::getline(file, line) && line.substr(0, 4) == "Item")
        {
            std::istringstream iss(line);
            std::string itemType;
            iss >> itemType;
            ItemType type;
            std::string path;

            if (itemType == "Item-Coin")
            {
                type = ItemType::COIN;
                path = PATH_COIN;
            }
            else if (itemType == "Item-RedMushroom")
            {
                type = ItemType::RED_MUSHROOM;
                path = PATH_REDMUSHROOM;
            }
            else if (itemType == "Item-PurpleMushroom")
            {
                type = ItemType::PURPLE_MUSHROOM;
                path = PATH_PURPLEMUSHROOM;
            }
            else if (itemType == "Item-GreenMushroom")
            {
                type = ItemType::GREEN_MUSHROOM;
                path = PATH_GREENMUSHROOM;
            }
            else if (itemType == "Item-BoomerangFlower")
            {
                type = ItemType::BOOMERANG_FLOWER;
                path = PATH_BOOMERANGFLOWER;
            }
            else if (itemType == "Item-SuperStar")
            {
                type = ItemType::SUPER_STAR;
                path = PATH_SUPPERSTAR;
            }

            if (path == "")
                break;

			float x, y, z;
			iss >> x >> y >> z;
			Vector3 position = { x, y, z };
			iss >> x >> y >> z;
			Vector3 scale = { x, y, z };
			iss >> x >> y >> z;
			Vector3 rotationAxis = { x, y, z };
			float rotationAngle;
			iss >> rotationAngle;
			bool isVisible;
			iss >> isVisible;

            std::shared_ptr<ItemData> item = ItemFactory::createItem(type, position, path, scale, rotationAxis, rotationAngle, CollisionManager::getInstance()->getDynamicsWorld());
            items.push_back(item);
        }
		m_items = items;

		//std::shared_ptr<Boomerang> boomerang = std::make_shared<Boomerang>();
		//boomerang->load(file);
		//m_boomerang = boomerang;
    }
}

StageModel::StageModel(int continu)
{
    loadFile();

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
    Vector3 startPosition = { 0.0f, -20.0f, 0.0f };
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    Vector3 rotateAxis = { 0.0f, 1.0f, 0.0f };
    float rotateAngle = 0.0f;


    Model model = LoadModel(PATH_BOOMERANG);

    BoundingBox modelBounds = GetModelBoundingBox(model);
    //calculate the point center of box
    Vector3 modelCenter = {
        (modelBounds.max.x + modelBounds.min.x) * 0.5f,
        (modelBounds.max.y + modelBounds.min.y) * 0.5f,
        (modelBounds.max.z + modelBounds.min.z) * 0.5f
    };


    Vector3 halfExtents = {
        (modelBounds.max.x - modelBounds.min.x) * scale.x * 0.5f,
        (modelBounds.max.y - modelBounds.min.y) * scale.y * 0.5f,
        (modelBounds.max.z - modelBounds.min.z) * scale.z * 0.5f
    };

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(
        startPosition.x + (modelCenter.x * scale.x),
        startPosition.y + (modelCenter.y * scale.y),
        startPosition.z + (modelCenter.z * scale.z)
    ));

    // Create box shape based on model dimensions
    std::shared_ptr<btCollisionShape>  itemShape = nullptr;
    itemShape = std::make_shared<btBoxShape>(btVector3(
        halfExtents.x, halfExtents.y, halfExtents.z));
    itemShape->setMargin(0.05f);



    btScalar mass = 0.0f;
    btVector3 localInertia(0, 0, 0);
    itemShape->calculateLocalInertia(mass, localInertia);


    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), itemShape.get(), localInertia);

    std::shared_ptr<btRigidBody> itemRigidBody = std::make_shared<btRigidBody>(rbInfo);

    //// Add block to the world
    dynamicsWorld->addRigidBody(itemRigidBody.get());
    m_boomerang = std::make_shared<Boomerang>(itemRigidBody, itemShape, motionState, PATH_BOOMERANG, model,
        startPosition, scale, rotateAxis, rotateAngle, dynamicsWorld, 40.0f);








    std::string characterName = GameData::getInstance().getPlayerName();
    std::string characterPath = "../../Assets\\Images\\Characters\\" + characterName + ".png";
    Texture2D texture4 = LoadTexture(characterPath.c_str());
    Rectangle sourceRec4 = { 0.0f, 0.0f, (float)texture4.width, (float)texture4.height };
    Rectangle destRec4 = { 180.0f, 50.0f, 100.0f, 100.0f };
    m_health = std::make_shared<Button>("", texture4, sourceRec4, destRec4, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

    Texture2D texture = LoadTexture("../../Assets/Icons/pause.png");
    Texture2D texture2 = LoadTexture("../../Assets/Icons/setting.png");
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destRec = { 50.0f, 50.0f, 100.0f, 100.0f };
    Rectangle sourceRec2 = { 0.0f, 0.0f, (float)texture2.width, (float)texture2.height };
    Rectangle destRec2 = { GetScreenWidth() - 150.0f, 50.0f, 100.0f, 100.0f };
    m_pause = std::make_shared<Button>("", texture, sourceRec, destRec, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    m_setting = std::make_shared<Button>("", texture2, sourceRec2, destRec2, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

    Texture2D texture3 = LoadTexture("../../Assets/Icons/clock.png");
    Rectangle sourceRec3 = { 0.0f, 0.0f, (float)texture3.width, (float)texture3.height };
    Rectangle destRec3 = { 1525.0f, 50.0f, 70.0f, 70.0f };
    m_timer = std::make_shared<Button>("", texture3, sourceRec3, destRec3, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}


StageModel::StageModel(std::shared_ptr<PlayerData> playerData, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode , std::vector<std::shared_ptr<BlockData>> mapData, std::vector<std::shared_ptr<Enemy>> enemies, std::vector<std::shared_ptr<ItemData>> items)
    : StageModel(cameraInitPos,cameraTarget, fovy, cameraMode)
{
    m_playerData = playerData;
    m_map = mapData;
	m_enemies = enemies;
	m_items = items;

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
    Vector3 startPosition = {0.0f, -20.0f, 0.0f};
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    Vector3 rotateAxis = { 0.0f, 1.0f, 0.0f };
    float rotateAngle = 0.0f;


    Model model = LoadModel(PATH_BOOMERANG);
    BoundingBox modelBounds = GetModelBoundingBox(model);
    Vector3 modelCenter = {
        (modelBounds.max.x + modelBounds.min.x) * 0.5f,
        (modelBounds.max.y + modelBounds.min.y) * 0.5f,
        (modelBounds.max.z + modelBounds.min.z) * 0.5f
    };
    Vector3 halfExtents = {
        (modelBounds.max.x - modelBounds.min.x) * scale.x * 0.5f,
        (modelBounds.max.y - modelBounds.min.y) * scale.y * 0.5f,
        (modelBounds.max.z - modelBounds.min.z) * scale.z * 0.5f
    };
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(
        startPosition.x + (modelCenter.x * scale.x),
        startPosition.y + (modelCenter.y * scale.y),
        startPosition.z + (modelCenter.z * scale.z)
    ));

    // Create box shape based on model dimensions
    std::shared_ptr<btCollisionShape>  itemShape = nullptr;
    itemShape = std::make_shared<btBoxShape>(btVector3(
        halfExtents.x, halfExtents.y, halfExtents.z));
    itemShape->setMargin(0.05f);

    btScalar mass = 0.0f;
    btVector3 localInertia(0, 0, 0);
    itemShape->calculateLocalInertia(mass, localInertia);


    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), itemShape.get(), localInertia);

    std::shared_ptr<btRigidBody> itemRigidBody = std::make_shared<btRigidBody>(rbInfo);

    //// Add block to the world
    dynamicsWorld->addRigidBody(itemRigidBody.get());
    m_boomerang = std::make_shared<Boomerang>(itemRigidBody, itemShape, motionState, PATH_BOOMERANG, model, 
        startPosition, scale, rotateAxis, rotateAngle, dynamicsWorld, 40.0f);


    createFire();



	std::string characterName = GameData::getInstance().getPlayerName();
	std::string characterPath = "../../Assets\\Images\\Characters\\" + characterName + ".png";
	Texture2D texture = LoadTexture(characterPath.c_str());
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = { 180.0f, 50.0f, 100.0f, 100.0f };
	m_health = std::make_shared<Button>("", texture, sourceRec, destRec, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}

StageModel::StageModel(Vector3 pos, Vector3 scale, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode)
    : StageModel(cameraInitPos, cameraTarget, fovy, cameraMode)
{
	m_playerData = createMarioModel(pos, scale);
    
    //initializeCamera();

}


StageModel::StageModel(Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode)
{
	m_cameraInitialPosition = cameraInitPos;
	m_camera.position = cameraInitPos;
	m_camera.target = cameraTarget;
	m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	m_camera.fovy = fovy;
	m_camera.projection = cameraMode;

	Texture2D texture = LoadTexture("../../Assets/Icons/pause.png");
	Texture2D texture2 = LoadTexture("../../Assets/Icons/setting.png");
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = { 50.0f, 50.0f, 100.0f, 100.0f };
	Rectangle sourceRec2 = { 0.0f, 0.0f, (float)texture2.width, (float)texture2.height };
	Rectangle destRec2 = { GetScreenWidth() - 150.0f, 50.0f, 100.0f, 100.0f };
	m_pause = std::make_shared<Button>("", texture, sourceRec, destRec, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
	m_setting = std::make_shared<Button>("", texture2, sourceRec2, destRec2, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D texture3 = LoadTexture("../../Assets/Icons/clock.png");
	Rectangle sourceRec3 = { 0.0f, 0.0f, (float)texture3.width, (float)texture3.height };
	Rectangle destRec3 = { 1525.0f, 50.0f, 70.0f, 70.0f };
	m_timer = std::make_shared<Button>("", texture3, sourceRec3, destRec3, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}

std::shared_ptr<Button> StageModel::getTimerButton() const
{
	return m_timer;
}

std::shared_ptr<Button> StageModel::getSettingButton() const
{
	return m_setting;
}

Camera3D& StageModel::getCamera()
{
    return m_camera;
}

std::vector<std::shared_ptr<Enemy>> StageModel::getEnemies()
{
	return m_enemies;
}

int StageModel::getCountFire()
{
    return countFire;
}

int StageModel::getCoins() const
{
	return coins;
}

void StageModel::setCoins(int coins)
{
	this->coins = coins;
}

void StageModel::setEnemies(std::vector<std::shared_ptr<Enemy>> enemies)
{
	m_enemies = enemies;
}

std::vector<std::shared_ptr<ItemData>> StageModel::getItems()
{
	return m_items;
}

float StageModel::getTimer()
{
	return timer;
}

void StageModel::setTimer(float timer)
{
	this->timer = timer;
}

void StageModel::setCountFire(int count)
{
    countFire = count;
}

int StageModel::getScore() const
{
	return score;
}

void StageModel::setScore(int score)
{
	this->score = score;
}


void StageModel::setItems(std::vector<std::shared_ptr<ItemData>> items)
{
	m_items = items;
}

std::shared_ptr<Button> StageModel::getHealthButton() const
{
	return m_health;
}

std::shared_ptr<Boomerang> StageModel::getBoomerang() const
{
    return m_boomerang;
}



std::vector<std::shared_ptr<Fire>> StageModel::getVectorFire()
{
    return fires;
}

void StageModel::setCamera(Camera3D camera)
{
    m_camera = camera;
}

Vector3 StageModel::getCameraPos()
{
    return m_camera.position;
}

std::shared_ptr<PlayerData> StageModel::getPlayerData() const
{
    return m_playerData;
}

std::shared_ptr<Button> StageModel::getPauseButton() const
{
    return m_pause;
}

std::shared_ptr<PlayerData> StageModel::createMarioModel(Vector3 position, Vector3 scale)
{
    std::shared_ptr<PlayerData> marioModel;
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    Vector3 forwardDir = { 1.0f, 0.0f, 0.0f };
    Vector3 positionMario = position;
    Vector3 scaleMario = scale;
    Vector3 rotationAxisMario = { 0.0f, 1.0f, 0.0f };
    Model playerModel = LoadModel(("../../Assets\\Models\\Characters\\" + GameData::getInstance().getPlayerName() + ".glb").c_str());
    BoundingBox modelBounds = GetModelBoundingBox(playerModel);

    // Calculate the arm span (distance along the X-axis)
    float armSpan = (modelBounds.max.x - modelBounds.min.x) * scaleMario.x;

    // Set the capsule radius to half the arm span
    float radius = armSpan * 0.5f - 0.2f;

    // Calculate height of the capsule based on the model's bounding box
    float height = (modelBounds.max.y - modelBounds.min.y) * scaleMario.y - 1.0f; // Height of the model

    // Adjust height to exclude spherical parts of the capsule
    float capsuleHeight = height - radius;
    if (capsuleHeight < 0) {
        capsuleHeight = 0; // Prevent negative height
    }

    // Define initial transformation for the player
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(positionMario.x, positionMario.y, positionMario.z));

    // Create capsule shape
    std::shared_ptr<btCollisionShape> playerShape = std::make_shared<btCapsuleShape>(radius, capsuleHeight);

    // Physics body setup remains the same
    btScalar mass = 75.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(btDefaultMotionState(startTransform));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), playerShape.get(), localInertia);

    std::shared_ptr<btRigidBody> playerRigidBody = std::make_shared<btRigidBody>(rbInfo);

    std::string modelPath = "../../Assets\\Models\\Characters\\" + GameData::getInstance().getPlayerName() + ".glb";
    marioModel = std::make_shared<PlayerData>(
        playerRigidBody,                               // std::shared_ptr<btRigidBody>
        playerShape,                                   // std::shared_ptr<btCollisionShape>
        motionState,								   // std::shared_ptr<btDefaultMotionState>
        modelPath,                                     // std::string
        forwardDir,                                    // Vector3
        positionMario,                                 // Vector3
        20.0f,                                         // float
        scaleMario,                                    // Vector3
        rotationAxisMario,                             // Vector3
        0.0f,                                          // float
        40000.0f,                                      // float
        5,                                           // int
        dynamicsWorld                                 // std::shared_ptr<btDynamicsWorld>
    );

    return marioModel;
}


 std::vector<std::shared_ptr<BlockData>> StageModel::getMap() const
{
    return m_map;
}

 void StageModel::setMap(std::vector<std::shared_ptr<BlockData>> map)
 {
     m_map = map;
 }

 void StageModel::createFire()
 {
    

     for (int i = 0; i < 20; i++)
     {
         std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
         Vector3 startPosition = { 0.0f, -50.0f, 0.0f };
         Vector3 scale = { 1.0f, 1.0f, 1.0f };
         Vector3 rotateAxis = { 0.0f, 1.0f, 0.0f };

         float rotateAngle = 0.0f;
         Model model = LoadModel(PATH_FIRE);
         BoundingBox modelBounds = GetModelBoundingBox(model);
         Vector3 modelCenter = {
             (modelBounds.max.x + modelBounds.min.x) * 0.5f,
             (modelBounds.max.y + modelBounds.min.y) * 0.5f,
             (modelBounds.max.z + modelBounds.min.z) * 0.5f
         };
         Vector3 halfExtents = {
             (modelBounds.max.x - modelBounds.min.x) * scale.x * 0.5f,
             (modelBounds.max.y - modelBounds.min.y) * scale.y * 0.5f,
             (modelBounds.max.z - modelBounds.min.z) * scale.z * 0.5f
         };
         btTransform startTransform;
         startTransform.setIdentity();
         startTransform.setOrigin(btVector3(
             startPosition.x + (modelCenter.x * scale.x),
             startPosition.y + (modelCenter.y * scale.y),
             startPosition.z + (modelCenter.z * scale.z)
         ));

         // Create box shape based on model dimensions
         std::shared_ptr<btCollisionShape>  itemShape = nullptr;
         itemShape = std::make_shared<btBoxShape>(btVector3(
             halfExtents.x, halfExtents.y, halfExtents.z));
         itemShape->setMargin(0.05f);

         btScalar mass = 0.0f;
         btVector3 localInertia(0, 0, 0);
         itemShape->calculateLocalInertia(mass, localInertia);


         std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(startTransform);
         btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), itemShape.get(), localInertia);

         std::shared_ptr<btRigidBody> itemRigidBody = std::make_shared<btRigidBody>(rbInfo);

         //// Add block to the world
         dynamicsWorld->addRigidBody(itemRigidBody.get());

         std::shared_ptr<Fire> fire = std::make_shared<Fire>(itemRigidBody, itemShape, motionState, PATH_FIRE, model, startPosition, scale, rotateAxis, rotateAngle, dynamicsWorld, 40.0f);
         fires.push_back(fire);
     }
     countFire = fires.size();


 }

