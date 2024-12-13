#include "Stage1Model.h"

Stage1Model::Stage1Model()
{
    m_width = 200;
    m_height = 2;
    m_depth = 9;
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = GameData::getInstance().getDynamicsWorld();

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
            m_map.push_back(std::shared_ptr<BlockData>(block));
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
            addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
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

//Stage1Model::Stage1Model(int width, int height, int depth, std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld)
//    : StageModel()
//{
    //m_width = width;
    //m_height = height;
    //m_depth = depth;

    //const float size = 2.5f;
    //const int middle = m_depth / 2;
    //const int heightLevel = 4;


    //Vector3 scale = { 1.0f, 1.0f, 1.0f };
    //Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    //float rotaionAngle = 0.0f;
    //// Helper lambdas
    //auto addBlock = [&](BlockType type, const std::string& path, const Vector3& position, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle) {
    //    auto block = BlockFactory::createBlock(type, std::move(dynamicsWorld), path, position, scale, rotationAxis, rotationAngle);
    //    if(block)
    //         m_map.push_back(std::shared_ptr<BlockData>(block));
    //    //if (type == BlockType::QuestionBlock)
    //    //{
    //    //    m_questionBlock.push_back(block);
    //    //}
    //    //else if (type == BlockType::NormalBrickBlock)
    //    //{
    //    //    m_normalBrickBlock.push_back(block);
    //    //}
    //    //else if (type == BlockType::PipeBlock)
    //    //{
    //    //    m_pipeBlock.push_back(block);
    //    //}
    //    //else if (type == BlockType::SupportivePipeBlock)
    //    //{
    //    //    m_supportivePipeBlock.push_back(block);
    //    //}
    //    return block;
    //    };

    //auto createBrickBlockGrid = [&]() {
    //    for (int i = 0; i < m_width; ++i) {
    //        if (i == 62 || i == 63 || i == 64 || i == 78 || i == 79 || i == 80 || i == 138 || i == 139)
    //            continue;

    //        for (int j = 0; j < m_height; ++j) {
    //            for (int k = 0; k < m_depth; ++k) {
    //                Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
    //                addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
    //            }
    //        }
    //    }
    //    };

    //auto createQuestionBlocks = [&]() {
    //    std::vector<int> questionBlockIndices = { 16, 20, 22, 21, 72, 85, 96, 99, 102, 120, 121, 152 };
    //    for (int i : questionBlockIndices) {
    //        Vector3 position = (i == 21 || i == 85 || i == 120 || i == 121) ?
    //            Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, size * middle * scale.z } :
    //            Vector3{ size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::QuestionBlock, PATH_QUESTIONBLOCK, position, scale, rotationAxis, rotaionAngle);
    //    }
    //    };

    //auto createNormalBlocks = [&]() {
    //    std::vector<int> normalBlockIndices = { 19, 21, 23, 71, 73, 74, 75, 76, 77, 78, 79, 82, 83, 84, 85, 90, 91, 109, 112, 113, 114, 119, 120, 121, 122, 150, 151, 153 };
    //    for (int i : normalBlockIndices) {
    //        Vector3 position = (i == 74 || i == 75 || i == 76 || i == 77 || i == 78 || i == 79 || i == 82 || i == 83 || i == 84 ||
    //            i == 112 || i == 113 || i == 114 || i == 119 || i == 122) ?
    //            Vector3{ size * i * scale.x, size * heightLevel * 2 * scale.y, size * middle * scale.z } :
    //            Vector3{ size * i * scale.x, size * heightLevel * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
    //    }
    //    };

    //auto createPipeBlocks = [&]() {
    //    std::vector<int> pipeBlockIndices = { 27, 40, 53 };
    //    float j = 1.0f;
    //    for (int i : pipeBlockIndices) {
    //        Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
    //        Vector3 position = { size * i * scale.x, size * j * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
    //        j++;
    //    }
    //    for (int i = -8; i <= 4; i += 3) {
    //        Vector3 scale1 = { 2.0f * scale.x, 3.0f * scale.y, 2.0f * scale.z };
    //        Vector3 position = { size * 145 * scale.x, size * i * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::PipeBlock, PATH_PIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
    //    }
    //    };

    //auto createSupportivePipeBlocks = [&]()
    //    {
    //        Vector3 scale1 = { 2.0f * scale.x , 2.0f * scale.y, 2.0f * scale.z };
    //        Vector3 position = { size * 144 * scale.x, size * (-7) * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::SupportivePipeBlock, PATH_SUPPORTIVEPIPEBLOCK, position, scale1, rotationAxis, rotaionAngle);
    //    };

    //auto createLeftRouletteBlocks = [&]() {
    //    for (int i = 126; i < 130; ++i)
    //    {
    //        for (int j = 2; j <= i - 124; ++j)
    //        {
    //            for (int k = middle - 1; k <= middle + 1; ++k)
    //            {
    //                Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
    //                auto rouletteBlock = BlockFactory::createBlock(BlockType::RouletteBlock, std::move(dynamicsWorld), PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle);
    //                m_map.push_back(std::shared_ptr<BlockData>(rouletteBlock));
    //            }
    //        }
    //    }
    //    };


    //auto createRightRouletteBlocks = [&]() {
    //    float rotaionAngle2 = 180.0f;
    //    for (int i = 131; i < 135; ++i)
    //    {
    //        for (int j = 2; j <= 136 - i; ++j)
    //        {
    //            for (int k = middle - 1; k <= middle + 1; ++k)
    //            {
    //                Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
    //                auto rouletteBlock = BlockFactory::createBlock(BlockType::RouletteBlock, std::move(dynamicsWorld), PATH_ROULETTEBLOCK, position, scale, rotationAxis, rotaionAngle2);
    //                m_map.push_back(std::shared_ptr<BlockData>(rouletteBlock));
    //            }
    //        }
    //    }
    //    };
    //auto createUnderground = [&]() {
    //    for (int i = 130; i < 149; ++i) {
    //        for (int j = -10; j < -8; ++j) {
    //            for (int k = 0; k < m_depth; ++k) {
    //                Vector3 position = { size * i * scale.x, size * j * scale.y, size * k * scale.z };
    //                addBlock(BlockType::BrickBlock, PATH_BRICKBLOCK, position, scale, rotationAxis, rotaionAngle);
    //            }
    //        }
    //    }
    //    };

    //auto createSpecificNormalBlocks = [&]() {
    //    for (int i = 134; i < 138; ++i) {
    //        Vector3 position = { size * i * scale.x, size * (-7) * scale.y, size * middle * scale.z };
    //        addBlock(BlockType::NormalBrickBlock, PATH_NORMALBRICKBLOCK, position, scale, rotationAxis, rotaionAngle);

    //    }
    //    };

    //// Main function calls
    //createBrickBlockGrid();
    //createQuestionBlocks();
    //createNormalBlocks();
    //createPipeBlocks();
    //createSupportivePipeBlocks();
    //createLeftRouletteBlocks();
    //createRightRouletteBlocks();
    //createUnderground();
    //createSpecificNormalBlocks();
//}

#include <iostream>
Stage1Model::~Stage1Model()
{

}

const std::vector<std::shared_ptr<BlockData>>& Stage1Model::getMap() const
{
    return m_map;
}



