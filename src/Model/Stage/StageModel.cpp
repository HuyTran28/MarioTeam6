#include "StageModel.h"
#include <iostream>



StageModel::StageModel(std::shared_ptr<PlayerData> playerData, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode , std::vector<std::shared_ptr<BlockData>> mapData, std::vector<std::shared_ptr<Enemy>> enemies, std::vector<std::shared_ptr<ItemData>> items)
    : StageModel(cameraInitPos,cameraTarget, fovy, cameraMode)
{
    m_playerData = playerData;
    m_map = mapData;
	m_enemies = enemies;
	m_items = items;


    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
    Vector3 startPosition = {0.0f, 5.0f, 0.0f};
    Vector3 scale = { 0.3f, 0.3f, 0.3f };
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
        startPosition, scale, rotateAxis, rotateAngle, dynamicsWorld, 10.0f);








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

void StageModel::setCamera(Camera3D camera)
{
    m_camera = camera;
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
        35000.0f,                                      // float
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

