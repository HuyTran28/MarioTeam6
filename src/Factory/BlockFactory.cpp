#include "BlockFactory.h"

BlockData* BlockFactory::createBlock(BlockType type, btDiscreteDynamicsWorld* dynamicsWorld, const std::string& modelPath, const Vector3& startPosition, const Vector3& scale, const Vector3& rotationAxis, const float& rotationAngle)
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

    // Thi?t l?p transform ban ??u và bù v? trí b?ng tâm Bounding Box
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(
        startPosition.x + (modelCenter.x * scale.x),
        startPosition.y + (modelCenter.y * scale.y),
        startPosition.z + (modelCenter.z * scale.z)
    ));

    // Create box shape based on model dimensions
    btCollisionShape* blockShape = nullptr;
    if (type == BlockType::PipeBlock)
    {
        blockShape = new btCylinderShape(btVector3(
            halfExtents.x, halfExtents.y, halfExtents.z));
        blockShape->setMargin(0.05f);
    }
    else
    {
        blockShape = new btBoxShape(btVector3(
            halfExtents.x, halfExtents.y, halfExtents.z
        ));
        blockShape->setMargin(0.1f);
    }



    btScalar mass = 0.0f;
    btVector3 localInertia(0, 0, 0);
    blockShape->calculateLocalInertia(mass, localInertia);


    btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, blockShape, localInertia);

    btRigidBody* blockRigidBody = new btRigidBody(rbInfo);

    // Add block to the world
    dynamicsWorld->addRigidBody(blockRigidBody);


    switch (type)
    {
    case BlockType::BrickBlock:
        return new BrickBlock(blockRigidBody, "BrickBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::NormalBrickBlock:
        return new NormalBrickBlock(blockRigidBody, "NormalBrickBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::PipeBlock:
        return new PipeBlock(blockRigidBody, "PipeBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::QuestionBlock:
        return new QuestionBlock(blockRigidBody, "QuestionBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::EmptyBlock:
        return new EmptyBlock(blockRigidBody, "EmptyBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::RouletteBlock:
        return new RouletteBlock(blockRigidBody, "FakeBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::SupportivePipeBlock:
        return new SupportivePipeBLock(blockRigidBody, "SupportivePipeBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    case BlockType::FlyBlock:
        return new FlyBlock(blockRigidBody, "FlyBlock", model, startPosition, scale, rotationAxis, rotationAngle, dynamicsWorld);
    default:
        nullptr;
    }
    return nullptr;
}