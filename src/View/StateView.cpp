#include "StateView.h"

void StateView::renderBlocks(std::vector<std::shared_ptr<BlockData>> map)
{
    /*BeginDrawing();
    ClearBackground(RAYWHITE);*/
    for (const auto& block : map)
    {
        btRigidBody* rigidBodyOfBlock = block->getRigidBody();
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
   // EndDrawing();
}
