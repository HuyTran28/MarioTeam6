#include "Stage1Model.h"
#include <iostream>
Stage1Model::Stage1Model() : StageModel(createMarioModel(Vector3{ 10.0f, 10.0f, 0.0f }, Vector3{0.9f, 0.9f, 0.9f}), Vector3{0.0f, 20.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}, 30.0f, CAMERA_PERSPECTIVE,
                            createMap(), createEnemies(), createItems())
{
	cloudScales = { 1.0f, 1.0f, 1.0f };
	cloudRotationsAxis = { 0.0f, 1.0f, 0.0f };
    Model cloud1 = LoadModel("../../Assets\\Models\\clouds.glb");


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



Stage1Model::~Stage1Model()
{

}

std::vector<std::shared_ptr<BlockData>> Stage1Model::createMap()
{
    std::vector<std::shared_ptr<BlockData>> map;

    m_width = 200;
    m_height = 2;
    m_depth = 9;
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    const float size = 2.5f;
    const int middle = m_depth / 2;
    const int heightLevel = 5;


    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    float rotaionAngle = 0.0f;
    // Helper lambdas
    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle) {

        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale, rotationAxis, rotationAngle);
        if (block)
            map.push_back(std::shared_ptr<BlockData>(block));

        return block;
        };

    addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, { 10.0, 12.0, 10.0 }, scale, rotationAxis, rotaionAngle);
    

    auto createBrickBlockGrid = [&]() {
        for (int i = 0; i < m_width; ++i) {
            if (i == 62 || i == 63 || i == 64 || i == 78 || i == 79 || i == 80 || i == 138 || i == 139)
                continue;

            for (int j = 0; j < m_height; ++j) {
                for (int k = 0; k < m_depth; ++k) {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
                }
            }
        }
        };

    auto createQuestionBlocks = [&]() {
        std::vector<int> questionBlockIndices = { 16, 20, 22, 21, 72, 85, 96, 99, 102, 120, 121, 152 };
        for (int i : questionBlockIndices) {
            Vector3 position = (i == 21 || i == 85 || i == 120 || i == 121) ?
                Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, size * middle * scale.z } :
                Vector3{ size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
            addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale, rotationAxis, rotaionAngle);
        }
        };

    auto createNormalBlocks = [&]() {
        std::vector<int> normalBlockIndices = { 19, 21, 23, 71, 73, 74, 75, 76, 77, 78, 79, 82, 83, 84, 85, 90, 91, 109, 112, 113, 114, 119, 120, 121, 122, 150, 151, 153 };
        for (int i : normalBlockIndices) {
            Vector3 position = (i == 74 || i == 75 || i == 76 || i == 77 || i == 78 || i == 79 || i == 82 || i == 83 || i == 84 ||
                i == 112 || i == 113 || i == 114 || i == 119 || i == 122) ?
                Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, size * middle * scale.z } :
                Vector3{ size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
            addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
        }
        };

    auto createPipeBlocks = [&]() {
        std::vector<int> pipeBlockIndices = { 27, 40, 53 };
        float j = 1.0f;
        for (int i : pipeBlockIndices) {
            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * i * scale.x, size * j * scale.y, size * middle * scale.z };

            
            btVector3 tmp = { position.x, position.y - 20, position.z};

            std::shared_ptr<PipeBlock> pipeBlock = std::dynamic_pointer_cast<PipeBlock>(BlockFactory::createBlock(BlockType::PipeBlock, dynamicsWorld, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle));
            pipeBlock->setNewPosition(tmp);
            map.push_back(pipeBlock);

            j++;
        }
        for (int i = -20; i <= 4; i += 3)
        {
            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position1 = { size * 145 * scale.x, size * i * scale.y, size * middle * scale.z };
            std::shared_ptr<PipeBlock> pipeBlock1 = std::dynamic_pointer_cast<PipeBlock>(BlockFactory::createBlock(BlockType::PipeBlock, dynamicsWorld, PATH_PIPEBLOCK, position1, scale1, rotationAxis, rotaionAngle));
            map.push_back(pipeBlock1);

            if (i == 4) {
                btVector3 tmp(-35, position1.y - 55 , position1.z -10);

                pipeBlock1->setNewPosition(tmp);
            }
        }
        

        };

    auto createSupportivePipeBlocks = [&]()
        {
            Vector3 scale1 = { 2.0f * scale.x , 2.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * 144 * scale.x, size * (-17) * scale.y, size * middle * scale.z };
            std::shared_ptr<SupportivePipeBLock> pipeBlock1 = std::dynamic_pointer_cast<SupportivePipeBLock>(BlockFactory::createBlock(BlockType::SupportivePipeBlock,
                dynamicsWorld, PATH_SUPPORTIVEPIPEBLOCK, position, scale1, rotationAxis, rotaionAngle));
            map.push_back(pipeBlock1);


            
            btVector3 tmp({10.0f, 70.0f, 0.0f});
            pipeBlock1->setNewPosition(tmp);
        };

    auto createLeftRouletteBlocks = [&]() {
        for (int i = 126; i < 130; ++i)
        {
            for (int j = 2; j <= i - 124; ++j)
            {
                for (int k = 1; k < m_depth - 1; ++k)
                {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::RouletteBlock, PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle);
                }
            }
        }
        };


    auto createRightRouletteBlocks = [&]() {
        float rotaionAngle2 = 180.0f;
        for (int i = 131; i < 135; ++i)
        {
            for (int j = 2; j <= 136 - i; ++j)
            {
                for (int k = 1; k < m_depth - 1; ++k)
                {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::RouletteBlock, PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle2);

                }
            }
        }
        };
    auto createUnderground = [&]() {
        for (int i = 130; i < 149; ++i) {
            for (int j = -20; j < -18; ++j) {
                for (int k = 0; k < m_depth; ++k) {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
                }
            }
        }
        };

    auto createSpecificNormalBlocks = [&]() {
        for (int i = 134; i < 138; ++i) {
            Vector3 position = { size * i * scale.x, size * (-15) * scale.y, size * middle * scale.z };
            addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);

        }
        };

    auto createIslandBlock = [&]()
        {
            Vector3 scaleIsland = { 13.0f, 13.0f, 13.0f };
            Vector3 rotationAxisIsland = { 1.0f, 0.0f, 0.0f };
            float rotaionAngleIsland = -90.0f;
            Vector3 position = { 430.0f, 1.0f, 6.0f };
            addBlock(BlockType::IslandBlock, PATH_ISLANDBLOCK, position, scaleIsland, rotationAxisIsland, rotaionAngleIsland);

        };


    // Main function calls
    createBrickBlockGrid();
    createQuestionBlocks();
    createNormalBlocks();
    createPipeBlocks();
    createSupportivePipeBlocks();
    createLeftRouletteBlocks();
    createRightRouletteBlocks();
    createUnderground();
    createSpecificNormalBlocks();
    createIslandBlock();
    return map;
}


std::vector<std::shared_ptr<Enemy>> Stage1Model::createEnemies()
{
    std::vector<std::shared_ptr<Enemy>> enemies;

    Vector3 rotaionAxisGoomba = { 0.0f, 1.0f, 0.0f };
    float rotationAngleGoomba = 0.0f;

    Vector3 rotaionAxisKoopa = { 0.0f, 1.0f, 0.0f };
    float rotationAngleKoopa = 0.0f;


    Vector3 scaleGoomba = { 0.7f, 0.7f, 0.7f };
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
    const float size = 2.5;
    const float Oy = 10;
    const float Oz = (m_depth * size) / 2;
    

   
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 55, 4, 10 }, forwardDirGoomba, scaleGoomba,  { 55, 4, 10 } , { 35, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 71.3546, 4, 15 }, forwardDirGoomba, scaleGoomba, { 71.3546, 4, 15 }, { 93.3127, 4, 15 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 71.3546, 4, 4.5 }, forwardDirGoomba, scaleGoomba, { 71.3546, 4, 4.5 }, { 93.3127, 4, 4.5 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 104, 4, 17 }, forwardDirGoomba, scaleGoomba, { 104, 4, 17 }, { 114.837, 4, 12 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 126.087, 4, 17 }, forwardDirGoomba, scaleGoomba, { 126.087, 4, 17 }, { 114.837, 4, 12 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 104.733, 4, 5 }, forwardDirGoomba, scaleGoomba, { 104.733, 4, 5 }, { 114.837, 4, 12 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 125.048, 4, 5 }, forwardDirGoomba, scaleGoomba, { 125.048, 4, 5 }, { 114.837, 4, 12 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);


  
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 250, 4, 10 }, forwardDirGoomba, scaleGoomba, { 250, 4, 10 }, { 230, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 255, 4, 10 }, forwardDirGoomba, scaleGoomba, { 255, 4, 10 }, { 235, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 260, 4, 10 }, forwardDirGoomba, scaleGoomba, { 260, 4, 10 }, { 240, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 265, 4, 10 }, forwardDirGoomba, scaleGoomba, { 265, 4, 10 }, { 245, 4, 10 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 230, 4, 10 }, forwardDirKoopa, scaleKoopa, { 230, 4, 10 }, { 220, 4, 10 }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 314.657, 6.76388,  16.8684 }, forwardDirGoomba, scaleGoomba, { 314.657, 6.76388,  16.8684 }, { 314.626, 6.63073, 2.69545 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 317.16, 9.32509,  3.02433 }, forwardDirGoomba, scaleGoomba, { 317.16, 9.32509,  3.02433 }, { 317.071,9.65208, 17.7685 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 319.693, 11.6266,  17.4452 }, forwardDirGoomba, scaleGoomba, { 319.693, 11.6266,  17.4452 }, { 319.663 ,11.6625, 3.54813 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    




    return enemies;
}

std::vector<std::shared_ptr<ItemData>> Stage1Model::createItems()
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

    
    addItem(ItemType::COIN, PATH_COIN, { 67.2905f, 9.0f, 10.0}, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 100.0f, 11.0f, 9.91975 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::PURPLE_MUSHROOM, PATH_PURPLEMUSHROOM, { 131.83f, 11.1415f, 10.1595f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    
    addItem(ItemType::COIN, PATH_COIN, { 186, 28, 10.0993 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 190, 28, 10.0993 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 194, 28, 10.0993 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);


    addItem(ItemType::COIN, PATH_COIN, { 100.0f, 11.0f, 9.91975 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::RED_MUSHROOM, PATH_REDMUSHROOM, { 272.533, 13.6688, 9.93939 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);

    addItem(ItemType::COIN, PATH_COIN, { 335, -35, 9.69735 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
    addItem(ItemType::COIN, PATH_COIN, { 339, -35, 9.69735 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);

	addItem(ItemType::GREEN_MUSHROOM, PATH_GREENMUSHROOM, { 20.0f, 10.0f, 9.69735 }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
 
    return items;
}

std::shared_ptr<Button> Stage1Model::getPauseButton() const
{
	return StageModel::getPauseButton();
}

std::vector<Model> Stage1Model::getClouds() const
{
	return clouds;
}

std::vector<Vector3> Stage1Model::getCloudPositions() const
{
	return cloudPositions;
}

Vector3 Stage1Model::getCloudScales() const
{
	return cloudScales;
}

Vector3 Stage1Model::getCloudRotationsAxis() const
{
	return cloudRotationsAxis;
}

std::vector<float> Stage1Model::getCloudRotationsAngle() const
{
	return cloudRotationsAngle;
}

Model Stage1Model::getHills() const
{
	return hills;
}

Vector3 Stage1Model::getHillsPosition() const
{
	return hillsPosition;
}

Vector3 Stage1Model::getHillsScale() const
{
	return hillsScale;
}

Vector3 Stage1Model::getHillsRotationAxis() const
{
	return hillsRotationAxis;
}

float Stage1Model::getHillsRotationAngle() const
{
	return hillsRotationAngle;
}








