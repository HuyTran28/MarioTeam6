#include "BlockFactory.h"

std::shared_ptr<BlockData> BlockFactory::createBlock(BlockType type, std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld, const std::string& modelPath, const Vector3& startPosition, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle)
{
    auto it = ModelStage::listModels.find(modelPath);
    Model model = {};
    if (it != ModelStage::listModels.end()) {
        model = it->second;
    }
    else
    {
        model = LoadModel(modelPath.c_str());
        if (model.meshCount > 0)
        {
            ModelStage::listModels[modelPath] = model;
        }
    }

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
    std::shared_ptr<btCollisionShape> blockShape = nullptr;
    if (type == BlockType::PipeBlock)
    {
        blockShape = std::make_shared<btCylinderShape>(btVector3(
            halfExtents.x, halfExtents.y, halfExtents.z));
        blockShape->setMargin(0.05f);
    }
    else
    {
            halfExtents.x, halfExtents.y, halfExtents.z
        ));
        blockShape->setMargin(0.1f);
    }



    btScalar mass = 0.0f;
    btVector3 localInertia(0, 0, 0);
    blockShape->calculateLocalInertia(mass, localInertia);


    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), blockShape.get(), localInertia);

    std::shared_ptr<btRigidBody> blockRigidBody = std::make_shared<btRigidBody>(rbInfo);

    // Add block to the world
    dynamicsWorld->addRigidBody(blockRigidBody.get());


    switch (type)
    {
	case BlockType::BrickBlock:
		return std::make_shared<BrickBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "BrickBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::NormalBrickBlock:
		return std::make_shared<NormalBrickBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "NormalBrickBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::PipeBlock:
		return std::make_shared<PipeBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "PipeBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::QuestionBlock:
		return std::make_shared<QuestionBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "QuestionBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::EmptyBlock:
		return std::make_shared<EmptyBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "EmptyBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::RouletteBlock:
		return std::make_shared<RouletteBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "RouletteBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::SupportivePipeBlock:
		return std::make_shared<PipeBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "SupportivePipeBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
	case BlockType::FlyBlock:
		return std::make_shared<FlyBlock>(blockRigidBody, blockShape, motionState, mass, localInertia, "FlyBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);

    default:
        nullptr;
    }

    return nullptr;
}