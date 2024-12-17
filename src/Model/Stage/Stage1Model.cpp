#include "Stage1Model.h"
#include <iostream>
Stage1Model::Stage1Model() : StageModel(createMarioModel(Vector3{ 0.0f, 10.0f, 10.0f }, Vector3{0.9f, 0.9f, 0.9f}), Vector3{0.0f, 20.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}, 30.0f, CAMERA_PERSPECTIVE,
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
    const int heightLevel = 4;


    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    float rotaionAngle = 0.0f;
    // Helper lambdas
    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle) {

        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale, rotationAxis, rotationAngle);
        if (block)
            map.push_back(std::shared_ptr<BlockData>(block));
        //if (type == BlockType::QuestionBlock)
        //{
        //    m_questionBlock.push_back(block);
        //}
        //else if (type == BlockType::NormalBrickBlock)
        //{
        //    m_normalBrickBlock.push_back(block);
        //}
        //else if (type == BlockType::PipeBlock)
        //{
        //    m_pipeBlock.push_back(block);
        //}
        //else if (type == BlockType::SupportivePipeBlock)
        //{
        //    m_supportivePipeBlock.push_back(block);
        //}
        return block;
        };

    addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, { 2.0, 12.0, 9.0 }, scale, rotationAxis, rotaionAngle);


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

            Vector3 newPos = position;
            newPos.y -= 100;

            std::shared_ptr<PipeBlock> pipeBlock = std::dynamic_pointer_cast<PipeBlock>(BlockFactory::createBlock(BlockType::PipeBlock, dynamicsWorld, PATH_PIPEBLOCK, position, scale, rotationAxis, rotaionAngle));
            pipeBlock->setNewPosition({0, -50, 0});
            map.push_back(pipeBlock);

            j++;
        }
        for (int i = -8; i <= 4; i += 3) {
            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * 145 * scale.x, size * i * scale.y, size * middle * scale.z };
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
        }

        };

    auto createSupportivePipeBlocks = [&]()
        {
            Vector3 scale1 = { 2.0f * scale.x , 2.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * 144 * scale.x, size * (-7) * scale.y, size * middle * scale.z };
            addBlock(BlockType::SupportivePipeBlock, PATH_SUPPORTIVEPIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
        };

    auto createLeftRouletteBlocks = [&]() {
        for (int i = 126; i < 130; ++i)
        {
            for (int j = 2; j <= i - 124; ++j)
            {
                for (int k = middle - 1; k <= middle + 1; ++k)
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
                for (int k = middle - 1; k <= middle + 1; ++k)
                {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::RouletteBlock, PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle2);

                }
            }
        }
        };
    auto createUnderground = [&]() {
        for (int i = 130; i < 149; ++i) {
            for (int j = -10; j < -8; ++j) {
                for (int k = 0; k < m_depth; ++k) {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
                }
            }
        }
        };

    auto createSpecificNormalBlocks = [&]() {
        for (int i = 134; i < 138; ++i) {
            Vector3 position = { size * i * scale.x, size * (-7) * scale.y, size * middle * scale.z };
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
    const float Oy = (m_height * 1.0) * size;
    const float Oz = (m_depth * size) / 2;

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 35, Oy, Oz }, forwardDirGoomba, scaleGoomba, { 35, Oy, Oz }, { 50, Oy, Oz }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 70, Oy ,Oz - (2 * size) }, forwardDirGoomba, scaleGoomba, { 70, Oy ,Oz - (2 * size) }, { 90, Oy, Oz - (2 * size) }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 70, Oy ,Oz - (2 * size) }, forwardDirGoomba, scaleGoomba, { 70, Oy ,Oz - (2 * size) }, { 95, Oy, Oz + (2 * size) }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 110, Oy, Oz - (2 * size) }, forwardDirGoomba, scaleGoomba, { 110, Oy, Oz - (2 * size) }, { 110, Oy, Oz + (2 * size) }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 120, Oy, Oz + (2 * size) }, forwardDirGoomba, scaleGoomba, { 120, Oy, Oz + (2 * size) }, { 120, Oy, Oz - (2 * size) }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 182.508, 21.6751, 10.1829 }, forwardDirGoomba, scaleGoomba, { 182.508, 21.6751, 10.1829 }, { 200, 21.6751, 10.1829 }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 250, Oy, Oz }, forwardDirGoomba, scaleGoomba, { 250, Oy, Oz }, { 230, Oy, Oz }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 255, Oy, Oz }, forwardDirGoomba, scaleGoomba, { 255, Oy, Oz }, { 235, Oy, Oz }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 260, Oy, Oz }, forwardDirGoomba, scaleGoomba, { 260, Oy, Oz }, { 240, Oy, Oz }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
    addEnemy(EnemyType::Goomba, PATH_GOOMBA, { 265, Oy, Oz }, forwardDirGoomba, scaleGoomba, { 265, Oy, Oz }, { 245, Oy, Oz }, speedGooba, rotaionAxisGoomba, rotationAngleGoomba);

    addEnemy(EnemyType::Koopa, PATH_KOOPA, { 230, Oy, Oz }, forwardDirKoopa, scaleKoopa, { 230, Oy, Oz }, { 220, Oy, Oz }, speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);

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

    
    addItem(ItemType::COIN, PATH_COIN, { 0.0f, 5.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);
	addItem(ItemType::RED_MUSHROOM, PATH_REDMUSHROOM, { 10.0f, 5.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 0.0f, dynamicsWorld);

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








