#include "ItemFactory.h"

std::shared_ptr<ItemData> ItemFactory::createItem(ItemType type, const Vector3& startPosition, const std::string& modelPath, 
    const Vector3& scale, const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> world)
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
    world->addRigidBody(itemRigidBody.get());


	switch (type)
	{
	case BOOMERANG_FLOWER:
        return std::make_shared <BoomerangFlower>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
	case RED_MUSHROOM:
        return std::make_shared <RedMushroom>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
	case GREEN_MUSHROOM:
        return std::make_shared <GreenMushroom>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
		break;
	case PURPLE_MUSHROOM:
        return std::make_shared <PurpleMushroom>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
	case SUPER_STAR:
        return std::make_shared <SuperStar>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
		break;
	case COIN:
        return std::make_shared <Coin>(itemRigidBody, itemShape, motionState, modelPath, model, startPosition, scale, rotationAxis, rotationAngle, world);
	default:
		return nullptr;
	}
}