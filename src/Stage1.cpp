#include "Stage1.h"
#include "player.h"
Stage1::Stage1() : m_width(0), m_depth(0), m_height(0) {}


Stage1::Stage1(int width, int height, int depth, btDiscreteDynamicsWorld* dynamicsWorld)
    : m_width(width), m_depth(depth), m_height(height)
{
    const float size = 2.5f;
    const int middle = m_depth / 2;
    const int heightLevel = 4;


    Vector3 scale = { 1.0f, 1.0f, 1.0f };

    // Helper lambdas
    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale) {
        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale);
        m_map.push_back(block);
        return block;
        };

    auto createBrickBlockGrid = [&]() {
        for (int i = 0; i < m_width; ++i) {
            if (i == 62 || i == 63 || i == 64 || i == 78 || i == 79 || i == 80 || i == 138 || i == 139)
                continue;

            for (int j = 0; j < m_height; ++j) {
                for (int k = 0; k < m_depth; ++k) {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale);
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
            addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale);
        }
        };

    auto createNormalBlocks = [&]() {
        std::vector<int> normalBlockIndices = { 19, 21, 23, 71, 73, 74, 75, 76, 77, 78, 79, 82, 83, 84, 85, 90, 91, 109, 112, 113, 114, 119, 120, 121, 122, 150, 151, 153 };
        for (int i : normalBlockIndices) {
            Vector3 position = (i == 74 || i == 75 || i == 76 || i == 77 || i == 78 || i == 79 || i == 82 || i == 83 || i == 84 ||
                i == 112 || i == 113 || i == 114 || i == 119 || i == 122) ?
                Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, size * middle * scale.z } :
                Vector3{ size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
            addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale);
        }
        };

    auto createPipeBlocks = [&]() {
        std::vector<int> pipeBlockIndices = { 27, 40, 53 };
        float j = 1.0f;
        for (int i : pipeBlockIndices) {
            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * i * scale.x, size * j * scale.y, size * middle * scale.z };
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1);
            j++;
        }
        for (int i = -8; i <= 4; i += 3) {
            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * 145 * scale.x, size * i * scale.y, size * middle * scale.z };
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1);
        }
        };

    auto createSupportivePipeBlocks = [&]()
        {
            Vector3 scale1 = { 2.0f * scale.x , 2.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * 144 * scale.x, size * (-7) * scale.y, size * middle * scale.z };
            addBlock(BlockType::SupportivePipeBlock, PATH_SUPPORTIVEPIPEBLOCK, position, scale1);

            position = { size * 144 * scale.x, size * 3 * scale.y, size * middle * scale.z };
            addBlock(BlockType::SupportivePipeBlock, PATH_SUPPORTIVEPIPEBLOCK, position, scale1);
        };

    auto createLeftRouletteBlocks = [&]() {
        for (int i = 126; i < 130; ++i)
        {
            for (int j = 2; j <= i - 124; ++j)
            {
                for (int k = middle - 1; k <= middle + 1; ++k)
                {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    auto rouletteBlock = BlockFactory::createBlock(BlockType::RouletteBlock, dynamicsWorld, PATH_ROULETTEBLOCK, position, scale);
                    m_map.push_back(rouletteBlock);
                }
            }
        }
        };


    auto createRightRouletteBlocks = [&]() {
        for (int i = 131; i < 135; ++i)
        {
            for (int j = 2; j <= 136 - i; ++j)
            {
                for (int k = middle - 1; k <= middle + 1; ++k)
                {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    auto rouletteBlock = BlockFactory::createBlock(BlockType::RouletteBlock, dynamicsWorld, PATH_ROULETTEBLOCK, position, scale);
                    m_map.push_back(rouletteBlock);
                }
            }
        }
        };
    auto createUnderground = [&]() {
        for (int i = 130; i < 149; ++i) {
            for (int j = -10; j < -8; ++j) {
                for (int k = 0; k < m_depth; ++k) {
                    Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                    addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale);
                }
            }
        }
        };

    auto createSpecificNormalBlocks = [&]() {
        for (int i = 134; i < 138; ++i) {
            Vector3 position = { size * i * scale.x, size * (-7) * scale.y, size * middle * scale.z };
            addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale);

        }
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
}

Stage1::~Stage1()
{

}


void Stage1::update(btRigidBody* player)
{
    for (auto& block : m_questionBlock)
    {
        if (block->checkCollisionWithPlayer(player))
        {
            Block* tmp = block;
            btDiscreteDynamicsWorld* dynamicsWorld = tmp->getDynamicsWorld();
            Vector3 position = tmp->getPosition();
            Vector3 scale = tmp->getScale();
            block = BlockFactory::createBlock(BlockType::EmptyBlock, dynamicsWorld, PATH_EMPTYBLOCK, position, scale);
            auto it = std::find(m_map.begin(), m_map.end(), tmp);
            if (it != m_map.end())
                *it = block;
            delete tmp;

        }
    }
    for (const auto& block : m_normalBrickBlock)
    {
        if (block->checkCollisionWithPlayer(player))
        {
        }
        if (block->getIsBouncing())
        {
            block->updateBounce();
            block->render();
        }
    }
}

void Stage1::draw()
{
    for (const auto& block : m_map)
    {
        if (block)
        {
            block->render();
        }
    }
}