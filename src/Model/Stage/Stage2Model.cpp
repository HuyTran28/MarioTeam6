#include "Stage2Model.h"



Stage2Model::Stage2Model() : StageModel(createMarioModel(Vector3{ 160.0f, 60.0f, 10.0f }, Vector3{ 0.9f, 0.9f, 0.9f }), Vector3{ 0.0f, 20.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 0.0f }, 30.0f, CAMERA_PERSPECTIVE,
    createMap(), createEnemies(), createItems())
{
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
}




Stage2Model::~Stage2Model()
{
}

std::vector<std::shared_ptr<BlockData>> Stage2Model::createMap()
{
    std::vector<std::shared_ptr<BlockData>> map;

    m_width = 110;
    m_height = 2;
    m_depth = 9;

    const float size = 2.5f;
    const int middle = m_depth / 2;
    const int heightLevel = 5;
    const int doubleHeightLevel = 8;

    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    float rotaionAngle = 180.0f;
    std::vector<int> brickBlockIndices = { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };
    std::vector<int> questionBlockIndices = { 20, 21, 31, 60, 70, 75, 92 };
    std::vector<int> normalBlockIndices = { 22, 30, 32, 34, 35, 36, 59, 61, 62, 69, 71, 90, 91, 93, 94 };

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    // Helper lambdas
    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle) {
        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale, rotationAxis, rotationAngle);
        map.push_back(std::shared_ptr<BlockData>(block));
        return block;
        };

    auto createBrickBlockGrid = [&]()
        {
            for (int i = 0; i < m_width; ++i)
            {
                if (std::find(brickBlockIndices.begin(), brickBlockIndices.end(), i) != brickBlockIndices.end())
                    continue;

                for (int j = 0; j < m_height; ++j) {
                    for (int k = 0; k < m_depth; ++k) {
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
                    }
                }
            }
        };

    auto createQuestionBlocks = [&]()
        {
            for (int i : questionBlockIndices)
            {
                Vector3 position;
                if (i >= 90)
                {
                    position = { size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
                }
                else if (i >= 59) {
                    position = (i == 60)
                        ? Vector3{ size * i * scale.x, size * heightLevel * 5.7f * scale.y,  (size * middle - 2) * scale.z }
                    : Vector3{ size * i * scale.x, size * heightLevel * 5.7f * scale.y, (size * middle + 2) * scale.z };
                }
                else {
                    position = (i == 20 || i == 21)
                        ? Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle - 2) * scale.z }
                    : Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle + 2) * scale.z };
                }
                auto questionBlock = addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale, rotationAxis, rotaionAngle);
            }
        };

    auto createNormalBlocks = [&]() {
        for (int i : normalBlockIndices)
        {
            Vector3 position;
            if (i >= 90)
            {
                position = { size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
            }
            else if (i >= 59) {
                position = (i == 59 || i == 61 || i == 62)
                    ? Vector3{ size * i * scale.x, size * heightLevel * 5.7f * scale.y, (size * middle - 2) * scale.z }
                : Vector3{ size * i * scale.x, size * heightLevel * 5.7f * scale.y, (size * middle + 2) * scale.z };
            }
            else if (i >= 34) {
                position = Vector3{ size * i * scale.x, size * heightLevel * 1.8f * scale.y, (size * middle + 2) * scale.z };
            }
            else {
                position = (i == 22)
                    ? Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle - 2) * scale.z }
                : Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle + 2) * scale.z };
            }
            auto normalBlock = addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
        }
        };

    for (int i = m_depth / 2 - 2; i <= m_depth / 2 + 2; ++i)
    {
        Vector3 position = { size * 94 * scale.x, size * heightLevel * 2 * scale.y, size * i * scale.z };
        addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

    }


    auto createSpecificFlyBlock = [&]()
        {
            Vector3 position = { size * 54 * scale.x, size * heightLevel * scale.y, (m_depth - 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * scale.y, 1.0f * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);


            position = { size * 54 * scale.x, size * heightLevel * 2.0f * scale.y, (m_depth / 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * 2.5f * scale.y, (m_depth - 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * 3.0f * scale.y, (m_depth / 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * 3.5f * scale.y, 1.0f * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * 4.0f * scale.y, (m_depth / 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

            position = { size * 54 * scale.x, size * heightLevel * 3.5f * scale.y, (m_depth - 2) * scale.z * size };
            addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale, rotationAxis, rotaionAngle);

        };

    auto createPipeStructure = [&]()
        {
            for (int i = 1; i <= (27); i += 3) {
                Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
                Vector3 position = { size * 83 * scale.x, size * i * scale.y , size * middle * scale.z };
                addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);

                std::shared_ptr<PipeBlock> pipeBlock1 = std::dynamic_pointer_cast<PipeBlock>(BlockFactory::
                    createBlock(BlockType::PipeBlock, dynamicsWorld, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle));
                map.push_back(pipeBlock1);

                if (i == 1)
                {
                    Vector3 scale1 = { 2.0f * scale.x, 2.0f * scale.y, 2.0f * scale.z };
                    Vector3 position1 = { size * 84 * scale.x, size * 2.5 * scale.y , size * middle * scale.z };


                    std::shared_ptr<SupportivePipeBLock> pipeBlock1 = std::dynamic_pointer_cast<SupportivePipeBLock>(BlockFactory::createBlock(BlockType::SupportivePipeBlock,
                        dynamicsWorld, PATH_SUPPORTIVEPIPEBLOCK, position1, scale1, rotationAxis, rotaionAngle));
                    map.push_back(pipeBlock1);
                    btVector3 tmp(-10, 70, 10);

                    pipeBlock1->setNewPosition(tmp);
                }

                if (i == 25) {
                    btVector3 tmp(17, -45.0f, 10);

                    pipeBlock1->setNewPosition(tmp);
                }
            }

        };

    auto createUpperBrickBlock = [&]()
        {
            for (int i = 55; i <= 85; ++i)
            {
                for (int j = 23; j < 25; ++j) {
                    for (int k = 0; k < m_depth; ++k) {
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
                    }
                }

            }
        };

    auto createRouletteBlocks = [&]()
        {
            for (int i = 46; i <= 52; ++i)
            {
                for (int j = 2; j <= i - 44; ++j) {
                    for (int k = 1; k < m_depth - 1; ++k) {
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::RouletteBlock, PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle - 180);
                    }
                }
            }
        };

    int tmp = 7;
    auto createSpecificBrickBlockArea = [&]()
        {
            for (int i = m_width - tmp; i < m_width; ++i)
            {
                for (int j = 0; j < 2; ++j) {
                    for (int k = m_depth; k <= m_depth + 80; ++k) {
                        if (k == m_depth + 40 || k == m_depth + 41 || k == m_depth + 42)
                            continue;
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);


                    }
                }
            }
        };


    //Vector3 position2 = { size * 106, size * 2, size * m_depth + 20 };
    //Vector3 scale2 = { 6.0f, 3.0f, 3.0f };
    //addBlock(BlockType::WaterBlock, PATH_WATERBLOCK, position2, scale2);


    std::vector<int> SpecificQuestionBlockIndices = { m_depth + 30, m_depth + 31, m_depth + 32 };
    std::vector<int> SpecificNormalBlockIndices = { m_depth + 32, m_depth + 33 };

    auto createSpecificQuestionBlockArea = [&]()
        {
            for (auto i : SpecificQuestionBlockIndices)
            {
                Vector3 position = (i == m_depth + 32) ?
                    Vector3{ size * (m_width - (tmp / 2 + 1)) * scale.x , size * heightLevel * 2 * scale.y, size * i * scale.z } :
                    Vector3({ size * (m_width - (tmp / 2 + 1)) * scale.x, size * heightLevel * scale.y , size * i * scale.z });
                addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale, rotationAxis, rotaionAngle);
            }
        };

    auto createSpecificNormalBlocksArea = [&]()
        {
            for (auto i : SpecificNormalBlockIndices)
            {
                Vector3 position = (i == m_depth + 33) ?
                    Vector3{ size * (m_width - (tmp / 2 + 1)) * scale.x, size * heightLevel * 2 * scale.y, size * i * scale.z } :
                    Vector3({ size * (m_width - (tmp / 2 + 1)) * scale.x, size * heightLevel * scale.y , size * i * scale.z });
                addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
            }
        };



    auto createSpecificPipeStructureArea = [&]()
        {

            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * (m_width - (tmp / 2 + 1)) * scale.x, size * 2.0f * scale.y , size * (m_depth + 48) * scale.z };

            std::shared_ptr<PipeBlock> pipeBlock1 = std::dynamic_pointer_cast<PipeBlock>(BlockFactory::createBlock(BlockType::PipeBlock,
                dynamicsWorld, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle));
            map.push_back(pipeBlock1);



            btVector3 tmp({ 20.0f, -25.0f, 0.0f });
            pipeBlock1->setNewPosition(tmp);

        };

    // Main function calls
    createBrickBlockGrid();
    createQuestionBlocks();
    createNormalBlocks();
    createSpecificFlyBlock();
    // createRouletteBlocks();
    createUpperBrickBlock();
    createPipeStructure();
    createSpecificBrickBlockArea();
    createSpecificQuestionBlockArea();
    createSpecificNormalBlocksArea();
    createSpecificPipeStructureArea();


    return map;
}

std::vector<std::shared_ptr<Enemy>> Stage2Model::createEnemies()
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

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 55, 4, 10 }, forwardDirGoomba, scaleGoomba, { 55, 4, 10 }, { 30, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 25, 4, 10 }, forwardDirKoopa, scaleKoopa, { 25, 4, 10 }, { 25, 4, 20 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 25, 4, 10 }, forwardDirKoopa, scaleKoopa, { 25, 4, 10 }, { 25, 4, 0 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);


    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 84, 26, 12 }, forwardDirGoomba, scaleGoomba, { 84, 26, 12 }, { 93, 26, 12 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);



    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 138, 61, 20.0947 }, forwardDirGoomba, scaleGoomba, { 137.293, 61, 20 }, { 137.313, 61, 2 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 145, 61, 12.5778 }, forwardDirGoomba, scaleGoomba, { 145, 61, 12.5778 }, { 165, 61, 12.5778 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 150, 61, 12.5778 }, forwardDirGoomba, scaleGoomba, { 150, 61, 12.5778 }, { 170, 61, 12.5778 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 155, 61, 12.5778 }, forwardDirKoopa, scaleKoopa, { 155, 61, 12.5778 }, { 175, 61, 12.5778 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);


    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 170, 61, 5 }, forwardDirKoopa, scaleKoopa, { 170, 61, 5 }, { 150, 61, 5 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 175, 61, 5 }, forwardDirGoomba, scaleGoomba, { 175, 61, 5 }, { 155, 61, 5 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 180, 61, 5 }, forwardDirGoomba, scaleGoomba, { 180, 61, 5 }, { 160, 61, 5 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);


    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 255, 4, 42 }, forwardDirGoomba, scaleGoomba, { 255, 4, 42 }, { 275, 4, 42 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 257, 4, 50 }, forwardDirGoomba, scaleGoomba, { 257, 4, 50 }, { 266, 4, 65.2282 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 273, 4.5, 51 }, forwardDirGoomba, scaleGoomba, { 273, 4.5, 51 }, { 266, 4.5, 65.2282 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 257, 4, 70 }, forwardDirGoomba, scaleGoomba, { 257, 4, 70 }, { 266, 4, 65.2282 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 273, 4.5, 70 }, forwardDirGoomba, scaleGoomba, { 273, 4.5, 70 }, { 266, 4, 65.2282 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);



    return enemies;
}

std::vector<std::shared_ptr<ItemData>> Stage2Model::createItems()
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


    addItem(ItemType::COIN, PATH_COIN, { 134.213, 28, 9.91009 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 135.246f, 15, 2.57203 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::PURPLE_MUSHROOM, PATH_PURPLEMUSHROOM, { 133.894 ,13.6733, 17.4 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);

    addItem(ItemType::GREEN_MUSHROOM, PATH_GREENMUSHROOM, { 134.3f, 32.4233, 17.6796 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 134.374, 41, 10 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::PURPLE_MUSHROOM, PATH_PURPLEMUSHROOM, { 134.60 , 44.9233, 2.2 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::RED_MUSHROOM, PATH_REDMUSHROOM, { 134.198, 44.9233, 17.5821 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::BOOMERANG_FLOWER, PATH_BOOMERANGFLOWER, { 135.012, 50.265, 9.79061 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);
    addItem(ItemType::GREEN_MUSHROOM, PATH_GREENMUSHROOM, { 264.461, 8.64154, 142.563 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, -90.0f, dynamicsWorld);


    return items;
}



std::shared_ptr<Button> Stage2Model::getPauseButton() const
{
    return StageModel::getPauseButton();
}

Model Stage2Model::getVolcano() const
{
    return volcano;
}

Vector3 Stage2Model::getVolcanoPosition() const
{
    return volcanoPosition;
}

Vector3 Stage2Model::getVolcanoScale() const
{
    return volcanoScale;
}

Vector3 Stage2Model::getVolcanoRotationAxis() const
{
    return volcanoRotationAxis;
}

float Stage2Model::getVolcanoRotationAngle() const
{
    return volcanoRotationAngle;
}

Model Stage2Model::getBowserCastle() const
{
    return BowserCastle;
}

Vector3 Stage2Model::getBowserCastlePosition() const
{
    return BowserCastlePosition;
}

Vector3 Stage2Model::getBowserCastleScale() const
{
    return BowserCastleScale;
}

Vector3 Stage2Model::getBowserCastleRotationAxis() const
{
    return BowserCastleRotationAxis;
}

float Stage2Model::getBowserCastleRotationAngle() const
{
    return BowserCastleRotationAngle;
}




