#include "Block.h"

bool Block::isPlayerCollidingWithBlock(btRigidBody* player)
{

    if (player && m_rigidBodyOfBlock)
    {

        btTransform playerTransform;
        player->getMotionState()->getWorldTransform(playerTransform);
        btVector3 playerMin, playerMax;
        player->getCollisionShape()->getAabb(playerTransform, playerMin, playerMax);


        btTransform blockTransform;
        m_rigidBodyOfBlock->getMotionState()->getWorldTransform(blockTransform);
        btVector3 blockMin, blockMax;
        m_rigidBodyOfBlock->getCollisionShape()->getAabb(blockTransform, blockMin, blockMax);



        bool isOverlappingX = (playerMax.x() >= blockMin.x()) && (playerMin.x() <= blockMax.x());
        bool isOverlappingY = (blockMin.y() - playerMax.y() < 0.1) && (blockMin.y() - playerMax.y() >= 0.0f);
        bool isOverlappingZ = (playerMax.z() >= blockMin.z()) && (playerMin.z() <= blockMax.z());


        return isOverlappingX && isOverlappingY && isOverlappingZ;
    }

    return false;
}

bool Block::checkCollisionWithPlayer(btRigidBody* player)
{

    if (m_name == "QuestionBlock" && m_rigidBodyOfBlock && player)
    {
        return isPlayerCollidingWithBlock(player);
    }
    else if (m_name == "NormalBrickBlock" && m_rigidBodyOfBlock && player)
    {
        if (isPlayerCollidingWithBlock(player))
        {
            m_isBouncing = true;
            m_velocity = VELOCCITY;

            if (m_bounceTime == 0.0f)
                m_bounceTime = TILE_DURATION;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void Block::updateBounce()
{
    float deltaTime = GetFrameTime();
    if (m_isBouncing)
    {
        btTransform blockTransform;
        m_rigidBodyOfBlock->getMotionState()->getWorldTransform(blockTransform);
        btVector3 originPosition = blockTransform.getOrigin();

        float height = m_velocity * (m_bounceTime * m_bounceTime - TILE_DURATION * m_bounceTime);


        blockTransform.setOrigin(btVector3(
            originPosition.x(),
            originPosition.y() - height, //update position of block 
            originPosition.z()
        ));
        m_rigidBodyOfBlock->getMotionState()->setWorldTransform(blockTransform);

        //decrease time bounce
        m_bounceTime -= deltaTime;


        if (m_bounceTime <= 0)
        {
            m_isBouncing = false;
            m_bounceTime = 0.0f;
            blockTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
            m_rigidBodyOfBlock->getMotionState()->setWorldTransform(blockTransform);

        }
    }
}

Vector3 Block::getPosition() const
{
    return m_position;
}

Vector3 Block::getScale() const
{
    return m_scale;
}

bool Block::getIsBouncing()
{
    return m_isBouncing;
}

btDiscreteDynamicsWorld* Block::getDynamicsWorld()
{
    return m_dynamicsWorld;
}

Block::~Block()
{
    if (m_rigidBodyOfBlock && m_dynamicsWorld) {
        m_dynamicsWorld->removeRigidBody(m_rigidBodyOfBlock);
    }
    delete m_rigidBodyOfBlock;
    m_rigidBodyOfBlock = nullptr;

    auto it = std::find_if(
        ModelStage::listModels.begin(),
        ModelStage::listModels.end(),
        [this](const auto& pair) { return pair.second.meshes == m_model.meshes; });

    if (it == ModelStage::listModels.end()) {
        UnloadModel(m_model);
    }
}

void Block::render()
{
    btTransform blockTransform;
    m_rigidBodyOfBlock->getMotionState()->getWorldTransform(blockTransform);
    btVector3 position = blockTransform.getOrigin();
    DrawModelEx(m_model, { position.getX(), position.getY(), position.getZ() }, { 0.0f, 1.0f, 0.0f }, 0.0f, m_scale, WHITE);
    //Get the collision shape from the rigid body
    btCollisionShape* shape = m_rigidBodyOfBlock->getCollisionShape();

    // Get the transform of the rigid body
    btTransform transform;
    m_rigidBodyOfBlock->getMotionState()->getWorldTransform(transform);

    // Convert Bullet's transform to your rendering library's format
    btVector3 origin = transform.getOrigin();
    btQuaternion rotation = transform.getRotation();
    Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
    // Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };

    if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
        btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
        btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
        Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };

        //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
        DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
    }
    // Add handling for other shape types here
    else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
        btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
        float radius = sphereShape->getMargin(); // Assuming margin is the radius
        //DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
        DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
    }
}

