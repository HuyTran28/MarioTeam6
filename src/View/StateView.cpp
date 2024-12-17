#include "StateView.h"


void StateView::renderBlocks(std::vector<std::shared_ptr<BlockData>> map)
{
    for (const auto& block : map)
    {
        std::shared_ptr<btRigidBody> rigidBodyOfBlock = block->getRigidBody();
        btTransform blockTransform;

        rigidBodyOfBlock->getMotionState()->getWorldTransform(blockTransform);

        btVector3 position = blockTransform.getOrigin();
        DrawModelEx(block->getModel(), { position.getX(), position.getY(), position.getZ() }, block->getRotationAxis(), block->getRotationAngle(), block->getScale(), WHITE);

        //Get the collision shape from the rigid body
        btCollisionShape* shape = rigidBodyOfBlock->getCollisionShape();

        if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
            btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
            btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
            Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };
            Vector3 boxPosition = { position.getX(), position.getY(), position.getZ() };
            //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
            DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black

        }
        // Add handling for other shape types here
        else if (shape->getShapeType() == CYLINDER_SHAPE_PROXYTYPE) {
            btCylinderShape* cylinderShape = static_cast<btCylinderShape*>(shape);
            btVector3 halfExtents = cylinderShape->getHalfExtentsWithMargin();

            // Determine the up-axis of the cylinder
            int upAxis = cylinderShape->getUpAxis();
            float radius = halfExtents[upAxis == 0 ? 1 : 0];
            float height = halfExtents[upAxis] * 2;
            Vector3 boxPosition = { position.getX(), position.getY() - 3.9f, position.getZ() };

            DrawCylinderWires(boxPosition, radius, radius, height, 32, BLACK);
        }

    }
}

void StateView::renderEnemies(std::vector<std::shared_ptr<Enemy>> enemies)
{
    for (auto enemy : enemies)
    {
        DrawModelEx(enemy->getPlayerModel(), {enemy->getPlayerPos().x, enemy->getPlayerPos().y, enemy->getPlayerPos().z}, 
            enemy->getPlayerRotationAxis(), enemy->getPlayerRotationAngle(), enemy->getPlayerScale(), WHITE);
        btCollisionShape* shape = enemy->getRigidBody()->getCollisionShape();

        // Get the transform of the rigid body
        btTransform transform;
        enemy->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Convert Bullet's transform to your rendering library's format
        btVector3 origin = transform.getOrigin();
        btQuaternion rotation = transform.getRotation();
        Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
        Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };

        if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
            btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
            btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
            Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

            //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
            DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
        }
        else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
            btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(shape);

            // Get the bounding box of the model
            BoundingBox modelBounds = GetModelBoundingBox(enemy->getPlayerModel());
            float modelHeight = (modelBounds.max.y - modelBounds.min.y) * enemy->getPlayerScale().y;
            float modelRadius = std::max((modelBounds.max.x - modelBounds.min.x), (modelBounds.max.z - modelBounds.min.z)) * enemy->getPlayerScale().z / 2.0f;

            // Adjust the capsule size to wrap around the model
            float radius = modelRadius * 1.1f; // Slightly larger than the model radius
            float halfHeight = (modelHeight / 2.0f) - radius;

            Vector3 startPos = { boxPosition.x, boxPosition.y - halfHeight, boxPosition.z };
            Vector3 endPos = { boxPosition.x, boxPosition.y + halfHeight, boxPosition.z };
            //DrawCapsule(startPos, endPos, radius, RED); // Draw the capsule in red
            DrawCapsuleWires(startPos, endPos, radius, 16, 16, BLACK); // Draw the capsule wireframe in black
        }
        // Add handling for other shape types here
        else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
            btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
            float radius = sphereShape->getMargin(); // Assuming margin is the radius
            //DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
            DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
        }
    }

    
}

void StateView::renderItems(std::vector<std::shared_ptr<ItemData>> items)
{
    for (const auto& item : items)
    {
        DrawModelEx(item->getModel(), {item->getPosition().x, item->getPosition().y, item->getPosition().z},
            item->getRotationAxis(), item->getRotationAngle(), item->getScale(), WHITE);

        btCollisionShape* shape = item->getRigidBody()->getCollisionShape();
        btTransform transform;
        item->getRigidBody()->getMotionState()->getWorldTransform(transform);

        // Convert Bullet's transform to your rendering library's format
        btVector3 origin = transform.getOrigin();
        btQuaternion rotation = transform.getRotation();
        Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
        Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };

        if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
            btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
            btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
            Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

            //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
            DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
        }
        else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
            btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(shape);

            // Get the bounding box of the model
            BoundingBox modelBounds = GetModelBoundingBox(item->getModel());
            float modelHeight = (modelBounds.max.y - modelBounds.min.y) * item->getScale().y;
            float modelRadius = std::max((modelBounds.max.x - modelBounds.min.x), (modelBounds.max.z - modelBounds.min.z)) * item->getScale().z / 2.0f;

            // Adjust the capsule size to wrap around the model
            float radius = modelRadius * 1.1f; // Slightly larger than the model radius
            float halfHeight = (modelHeight / 2.0f) - radius;

            Vector3 startPos = { boxPosition.x, boxPosition.y - halfHeight, boxPosition.z };
            Vector3 endPos = { boxPosition.x, boxPosition.y + halfHeight, boxPosition.z };
            //DrawCapsule(startPos, endPos, radius, RED); // Draw the capsule in red
            DrawCapsuleWires(startPos, endPos, radius, 16, 16, BLACK); // Draw the capsule wireframe in black
        }
        // Add handling for other shape types here
        else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
            btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
            float radius = sphereShape->getMargin(); // Assuming margin is the radius
            //DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
            DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
        }

    }
}
