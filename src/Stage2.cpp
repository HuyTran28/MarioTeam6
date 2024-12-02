
#include "Stage2.h"






void Stage2::update(btRigidBody* player)
{

}

Stage2::Stage2(int width, int height, int depth, btDiscreteDynamicsWorld* dynamicsWorld)
    : m_width(width), m_depth(depth), m_height(height)
{
    const float size = 2.5f;
    const int middle = m_depth / 2;
    const int heightLevel = 4;
    const int doubleHeightLevel = 8;
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
    std::vector<int> brickBlockIndices = { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };
    std::vector<int> questionBlockIndices = { 20, 21, 31, 60, 70, 75, 92 };
    std::vector<int> normalBlockIndices = { 22, 30, 32, 34, 35, 36, 59, 61, 62, 69, 71, 90, 91, 93, 94 };

    // Helper lambdas
    auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale) {
        auto block = BlockFactory::createBlock(type, dynamicsWorld, path, position, scale);
        m_map.push_back(block);
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
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale);
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
                        ? Vector3{ size * i * scale.x, size * heightLevel * 4 * scale.y,  (size * middle - 2) * scale.z }
                    : Vector3{ size * i * scale.x, size * heightLevel * 4 * scale.y, (size * middle + 2) * scale.z };
                }
                else {
                    position = (i == 20 || i == 21)
                        ? Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle - 2) * scale.z }
                    : Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle + 2) * scale.z };
                }
                auto questionBlock = addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale);
                m_questionBlock.push_back(questionBlock);
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
                    ? Vector3{ size * i * scale.x, size * heightLevel * 4 * scale.y, (size * middle - 2) * scale.z }
                : Vector3{ size * i * scale.x, size * heightLevel * 4 * scale.y, (size * middle + 2) * scale.z };
            }
            else if (i >= 34) {
                position = Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, (size * middle + 2) * scale.z };
            }
            else {
                position = (i == 22)
                    ? Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle - 2) * scale.z }
                : Vector3{ size * i * scale.x, size * heightLevel * scale.y, (size * middle + 2) * scale.z };
            }
            auto normalBlock = addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale);
            m_normalBrickBlock.push_back(normalBlock);
        }
        };

    for (int i = m_depth / 2 - 2; i <= m_depth / 2 + 2; ++i)
    {
        Vector3 position = { size * 94 * scale.x, size * heightLevel * 2 * scale.y, size * i * scale.z };
        auto flylBlock = addBlock(BlockType::FlyBlock, PATH_FLYBLOCK, position, scale);
        m_normalBrickBlock.push_back(flylBlock);
    }


    auto createPipeStructure = [&]()
        {
            for (int i = 1; i <= (13); i += 2) {
                Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
                Vector3 position = { size * 83 * scale.x, size * i * scale.y , size * middle * scale.z };
                addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1);
            }
        };

    auto createSupportivePipeBlocks = [&]()
        {
            for (int i = 55; i <= 85; ++i)
            {
                for (int j = 10; j < 12; ++j) {
                    for (int k = 0; k < m_depth; ++k) {
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale);
                    }
                }
                if (i == 84 || i == 82) {
                    Vector3 scale1 = { 2.0f * scale.x, 2.0f * scale.y, 2.0f * scale.z };
                    Vector3 position = { size * i * scale.x, (i == 84 ? size * 3 * scale.y : size * 13 * scale.y), size * middle * scale.z };
                    addBlock(BlockType::SupportivePipeBlock, PATH_SUPPORTIVEPIPEBLOCK, position, scale1);
                }
            }
        };

    auto createRouletteBlocks = [&]()
        {
            for (int i = 46; i <= 52; ++i)
            {
                for (int j = 2; j <= i - 44; ++j) {
                    for (int k = middle - 1; k <= middle + 1; ++k) {
                        Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
                        addBlock(BlockType::RouletteBlock, PATH_ROULETTEBLOCK, position, scale);
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
                        addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale);


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
                addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale);
            }
        };

    auto createSpecificNormalBlocksArea = [&]()
        {
            for (auto i : SpecificNormalBlockIndices)
            {
                Vector3 position = (i == m_depth + 33) ?
                    Vector3{ size * (m_width - (tmp / 2 + 1)) * scale.x, size * heightLevel * 2 * scale.y, size * i * scale.z } :
                    Vector3({ size * (m_width - (tmp / 2 + 1)) * scale.x, size * heightLevel * scale.y , size * i * scale.z });
                addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale);
            }
        };



    auto createSpecificPipeStructureArea = [&]()
        {

            Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
            Vector3 position = { size * (m_width - (tmp / 2 + 1)) * scale.x, size * 2.0f * scale.y , size * (m_depth + 48) * scale.z };
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1);

            position = { size * (m_width - (tmp / 2 + 1)) * scale.x, size * 2.5f * scale.y, size * (m_depth + 58) * scale.z };
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1);

        };

    // Main function calls
    createBrickBlockGrid();
    createQuestionBlocks();
    createNormalBlocks();
    createRouletteBlocks();
    createSupportivePipeBlocks();
    createPipeStructure();
    createSpecificBrickBlockArea();
    createSpecificQuestionBlockArea();
    createSpecificNormalBlocksArea();
    createSpecificPipeStructureArea();
}


void Stage2::draw()
{
    for (const auto& block : m_map)
    {
        block->render();
    }
}

