#include "Stage3Model.h"



Stage3Model::Stage3Model() : StageModel(createMarioModel(Vector3{ 0.0f, 5.0f, 0.0f }, Vector3{ 0.9f, 0.9f, 0.9f }), Vector3{ 0.0f, 100.0f, 0.0f }, Vector3{ -20.0f, 70.0f, 40.0f }, 200.0f, CAMERA_PERSPECTIVE,
    createMap(), createEnemies(), createItems())
{


    cloudScales = { 1.0f, 1.0f, 1.0f };
    cloudRotationsAxis = { 0.0f, 1.0f, 0.0f };
    Model cloud1 = LoadModel("../../Assets\\Models\\clouds.glb");
    volcano = LoadModel("../../Assets\\Models\\volcanoHill.glb");
    volcanoPosition = { 360.0f, -120.0f, 60.0f };
    volcanoScale = { 3.0f, 3.0f, 3.0f };
    volcanoRotationAxis = { 0.0f, 1.0f, 0.0f };
    volcanoRotationAngle = 0.0f;

    BowserCastle = LoadModel("../../Assets\\Models\\BowserCastle\\castle.glb");
    BowserCastlePosition = { 400.0f, -20.0f, 210.0f };
    BowserCastleScale = { 1.0f, 1.0f, 1.0f };
    BowserCastleRotationAxis = { 0.0f, 1.0f, 0.0f };
    BowserCastleRotationAngle = 270.0f;


    for (int i = 0; i < 10; i++)
    {
        Vector3 cloud1Position = { 0.0f + 30.0f * i, 25.0f, -60.0f };
        float cloud1RotationAngle = 90.0f;
        cloudPositions.push_back(cloud1Position);
        cloudRotationsAngle.push_back(cloud1RotationAngle);
        clouds.push_back(cloud1);
    }

    for (int i = 0; i < 10; i++)
    {
        Vector3 cloud1Position = { 0.0f + 30.0f * i, -120.0f, 0.0f };
        float cloud1RotationAngle = 90.0f;
        cloudPositions.push_back(cloud1Position);
        cloudRotationsAngle.push_back(cloud1RotationAngle);
        clouds.push_back(cloud1);
    }

    for (int i = 0; i < 12; i++)
    {
        Vector3 cloud1Position = { -60.0f + 30.0f * i, 40.0f, 0.0f };
        float cloud1RotationAngle = 90.0f;
        cloudPositions.push_back(cloud1Position);
        cloudRotationsAngle.push_back(cloud1RotationAngle);
        clouds.push_back(cloud1);
    }


    hills = LoadModel("../../Assets\\Models\\mountain.glb");
    hillsPosition = { 80.0f, -80.0f, -100.0f };
    hillsScale = { 2.0f, 2.0f, 2.0f };
    hillsRotationAxis = { 0.0f, 1.0f, 0.0f };
    hillsRotationAngle = 0.0f;
}




Stage3Model::~Stage3Model()
{
}

std::vector<std::shared_ptr<BlockData>> Stage3Model::createMap()
{
    std::vector<std::shared_ptr<BlockData>> map;

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle) {
        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale, rotationAxis, rotationAngle);
        map.push_back(std::shared_ptr<BlockData>(block));
        return block;
        };

    Vector3 position = { 0.0f, 0.0f, 0.0f };
    Vector3 scale = { 3.0f, 3.0f, 3.0f };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    float rotaionAngle = 0.0f;
    addBlock(BlockType::GroundBlock, PATH_GROUNDBLOCK, position, scale, rotationAxis, rotaionAngle);


    Vector3 position2 = { 25.0f, 10.0f, 0.0f };
    Vector3 scale2 = { 4.0f, 8.0f, 4.0f };
    Vector3 rotationAxis2 = { 0.0f, 1.0f, 0.0f };
    float rotationAngle2 = 0.0f;


    for (float z = 30.0f; z >= -30.0f; z -= 9.0f) {
        position2 = { 40.0f, 23.0f, z };
        addBlock(BlockType::WallBlock1, PATH_WALLBLOCK1, position2, scale2, rotationAxis2, rotationAngle2);
    }

    for (float x = 20.0f; x >= -20.0f; x -= 10.0f) {
        position2 = { x, 23.0f, 46 };
        addBlock(BlockType::WallBlock2, PATH_WALLBLOCK2, position2, scale2, rotationAxis2, rotationAngle2);
    }


    for (float x = 20.0f; x >= -20.0f; x -= 10.0f) {
        position2 = { x, 23.0f, -45 };
        addBlock(BlockType::WallBlock3, PATH_WALLBLOCK3, position2, scale2, rotationAxis2, rotationAngle2);
    }


    scale2 = { 4.0f, 8.0f, 80.0f };
    // position2 = { 32.0f, 23.0f, -41.0f};
    position2 = { 33.3f, 23.0f, -39.0f };
    addBlock(BlockType::WallBlock4, PATH_WALLBLOCK4, position2, scale2, rotationAxis2, rotationAngle2);

    scale2 = { 4.0f, 8.0f, 35.0f };
    // position2 = { 32.0f, 23.0f, -41.0f};
    position2 = { 32.0f, 23.0f, 41.0f };
    addBlock(BlockType::WallBlock4, PATH_WALLBLOCK5, position2, scale2, rotationAxis2, rotationAngle2);



    return map;
}

std::vector<std::shared_ptr<Enemy>> Stage3Model::createEnemies()
{
    std::vector<std::shared_ptr<Enemy>> enemies;

    Vector3 rotaionAxisGoomba = { 0.0f, 1.0f, 0.0f };
    float rotationAngleGoomba = 0.0f;

    Vector3 rotaionAxisKoopa = { 0.0f, 1.0f, 0.0f };
    float rotationAngleKoopa = 0.0f;


    Vector3 scaleGoomba = { 1.0f, 1.0f, 1.0f };
    Vector3 scaleKoopa = { 0.8f, 0.8f, 0.8f };

    Vector3 forwardDirGoomba = { 0, 0, 1 };
    Vector3 forwardDirKoopa = { 0, 0, 1 };

    float speedGooba = 5.0f;
    float speedKoopa = 5.0f;

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
    auto addEnemy = [&](EnemyType type, const std::string& path, const Vector3& position, const Vector3 forwardDir, const Vector3& scale,
        const Vector3& pointA, const Vector3& pointB, const float& speed, const Vector3& rotationAxis, const float& rotationAngle)
        {
            auto enemy = EnemyFactory::createEnemy(type, dynamicsWorld, path, position, forwardDir, rotationAxis, rotationAngle, scale, speed, pointA, pointB);
            if (enemy)
                enemies.push_back(std::shared_ptr<Enemy>(enemy));
        };


    

    //26.5789 1.08211 - 28.6094
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 26, 1, -28 }, forwardDirGoomba, scaleGoomba, { 26, 1, -28 }, { 27, 1, 1 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 26, 1, 31}, forwardDirGoomba, scaleGoomba, { 26, 1, 31 }, { 27, 1, 1 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);


    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 20, 1, 33 }, forwardDirGoomba, scaleGoomba, { 20, 1, 33 }, { -3, 1, 33 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { -25, 1, 33 }, forwardDirGoomba, scaleGoomba, { -25, 1, 33 }, { -3, 1, 33 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 20, 1, -32 }, forwardDirKoopa, scaleKoopa, { 20, 1, -32 }, { -2, 1, -32 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { -24, 1, -32 }, forwardDirKoopa, scaleKoopa, { -24, 1, -32 }, { -2, 1, -32 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    


    return enemies;
}

std::vector<std::shared_ptr<ItemData>> Stage3Model::createItems()
{
    std::vector < std::shared_ptr<ItemData>> items;

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    auto addItem = [&](ItemType type, const std::string& modelPath, const Vector3& position, const Vector3& scale,
        const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> world)
        {
            auto item = ItemFactory::createItem(type, position, modelPath, scale, rotationAxis, rotationAngle, world);
            if (item)
                items.push_back(std::shared_ptr<ItemData>(item));
        };


    addItem(ItemType::COIN, PATH_COIN, { -36, 3, 24 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::RED_MUSHROOM, PATH_REDMUSHROOM, { -36, 3, -22 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::GREEN_MUSHROOM, PATH_GREENMUSHROOM, { 18, 3, -22 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::BOOMERANG_FLOWER, PATH_BOOMERANGFLOWER, { 16, 3, 26 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 0, 3, 25 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 0, 3, -25 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);


    //addItem(ItemType::PURPLE_MUSHROOM, PATH_PURPLEMUSHROOM, { 133.894 ,13.6733, 17.4 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);*/


    return items;
}



std::shared_ptr<Button> Stage3Model::getPauseButton() const
{
    return StageModel::getPauseButton();
}

std::vector<Model> Stage3Model::getClouds() const
{
    return clouds;
}

std::vector<Vector3> Stage3Model::getCloudPositions() const
{
    return cloudPositions;
}

Vector3 Stage3Model::getCloudScales() const
{
    return cloudScales;
}

Vector3 Stage3Model::getCloudRotationsAxis() const
{
    return cloudRotationsAxis;
}

std::vector<float> Stage3Model::getCloudRotationsAngle() const
{
    return cloudRotationsAngle;
}

Model Stage3Model::getHills() const
{
    return hills;
}

Vector3 Stage3Model::getHillsPosition() const
{
    return hillsPosition;
}

Vector3 Stage3Model::getHillsScale() const
{
    return hillsScale;
}

Vector3 Stage3Model::getHillsRotationAxis() const
{
    return hillsRotationAxis;
}

float Stage3Model::getHillsRotationAngle() const
{
    return hillsRotationAngle;
}

Model Stage3Model::getVolcano() const
{
    return volcano;
}

Vector3 Stage3Model::getVolcanoPosition() const
{
    return volcanoPosition;
}

Vector3 Stage3Model::getVolcanoScale() const
{
    return volcanoScale;
}

Vector3 Stage3Model::getVolcanoRotationAxis() const
{
    return volcanoRotationAxis;
}

float Stage3Model::getVolcanoRotationAngle() const
{
    return volcanoRotationAngle;
}

Model Stage3Model::getBowserCastle() const
{
    return BowserCastle;
}

Vector3 Stage3Model::getBowserCastlePosition() const
{
    return BowserCastlePosition;
}

Vector3 Stage3Model::getBowserCastleScale() const
{
    return BowserCastleScale;
}

Vector3 Stage3Model::getBowserCastleRotationAxis() const
{
    return BowserCastleRotationAxis;
}

float Stage3Model::getBowserCastleRotationAngle() const
{
    return BowserCastleRotationAngle;
}




